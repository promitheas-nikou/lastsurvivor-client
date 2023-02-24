#include "BasicConveyorTile.h"
#include "ResourceLoader.h"
#include "World.h"


int BasicConveyorTile::MINING_RESISTANCE;
ToolType BasicConveyorTile::TOOL_TYPE;
std::string BasicConveyorTile::NAME;
int BasicConveyorTile::CONVEYOR_MAX_ITEMS = 1;
float BasicConveyorTile::CONVEYOR_ITEMS_DIST;
float BasicConveyorTile::CONVEYOR_SPEED;
ALLEGRO_BITMAP* BasicConveyorTile::TEXTURES[16];
const LootBundle* BasicConveyorTile::DROP;
const std::string BasicConveyorTile::ID = "tiles.basic_conveyor";

BasicConveyorTile::BasicConveyorTile(World* w, int x, int y) : DirectedTile(w, x, y), queue(CONVEYOR_MAX_ITEMS)
{

}

BasicConveyorTile::BasicConveyorTile(World* w, int x, int y, Direction d) : DirectedTile(w, x, y, d), queue(CONVEYOR_MAX_ITEMS)
{

}

std::string BasicConveyorTile::GetID() const
{
	return ID;
}

bool BasicConveyorTile::IsTransparent() const
{
	return false;
}

bool BasicConveyorTile::CanWalkThrough() const
{
	return false;
}

Tool::ToolType BasicConveyorTile::GetOptimalToolType() const
{
	return TOOL_TYPE;
}

float BasicConveyorTile::GetMiningResistance() const
{
	return MINING_RESISTANCE;
}

std::string BasicConveyorTile::GetName() const
{
	return NAME;
}

bool BasicConveyorTile::DoesTickUpdates() const
{
	return true;
}

void BasicConveyorTile::TickUpdate(uint64_t T)
{
	if (lastT >= T)
		return;
	lastT = T;
	world->GetTileRelative(xpos, ypos, direction)->TickUpdate(T);
	ItemDescriptor front;

	if (queue.GetCurSize())
	{
		float& f = queue.GetFront().prog;
		f = std::max(0.f, f - CONVEYOR_SPEED);
	}

	for (int i = 1; i < queue.GetCurSize(); i++) {
		float& f2 = queue.Get(i).prog;
		float& f1 = queue.Get(i - 1).prog;
		f2 = std::max(f2 - CONVEYOR_SPEED, f1 + CONVEYOR_ITEMS_DIST);
	}

	if (queue.TryPeekFront(&front))
	{
		if (front.prog <= 0.00001)
		{
			Item* newItem = world->GetTileRelative(xpos, ypos, direction)->PushItem(front.item, -direction, this);
			if (newItem)
				queue.GetFront().item = newItem;
			else
				queue.TryPop(nullptr);
		}
	}

	world->GetTileRelative(xpos, ypos, direction << 1)->TickUpdate(T);
	world->GetTileRelative(xpos, ypos, direction >> 1)->TickUpdate(T);
	Tile* t = world->GetTileRelative(xpos, ypos, direction >> 2);
	t->TickUpdate(T);



	if (queue.GetCurSize())
		if (1.f - queue.GetBack().prog < CONVEYOR_ITEMS_DIST)
			return;

	t->PushItem(PushItem(t->PullItem(direction, this), -direction, t), direction, this);
}

Tile* BasicConveyorTile::Clone(World* w, int x, int y) const
{
	return new BasicConveyorTile(w,x,y);
}

Tile* BasicConveyorTile::Clone(World* w, int x, int y, Direction d) const
{
	return new BasicConveyorTile(w,x,y,d);
}

Item* BasicConveyorTile::PushItem(Item* i, Direction d, ItemIOInterface* from)
{
	if (i == nullptr)
		return nullptr;
	if (i->GetAmount() > 1)
	{
		Item* r = PushItem(i->Clone()->SetAmountX(1), d, from);
		Item* v = (r && r->GetAmount())?i:i->RemoveAmountX(1);
		delete r;
		return v;
	}
	if (queue.GetCurSize()==0)
	{
		return queue.TryPush(ItemDescriptor(1.f, d, i))?nullptr:i;
	}
	if (1.f - queue.GetBack().prog < CONVEYOR_ITEMS_DIST)
		return i;
	return queue.TryPush(ItemDescriptor(1.f, d, i)) ? nullptr : i;
}

Item* BasicConveyorTile::PullItem(Direction d, ItemIOInterface* to)
{
	return nullptr;
}

void BasicConveyorTile::Draw() const
{
	al_draw_bitmap(TEXTURES[((uint8_t)direction)*4+(((lastT))%4)], xpos * 128, ypos * 128, 0);
}

void BasicConveyorTile::SerializeToStream(std::ostream& file)
{
	DirectedTile::SerializeToStream(file);
	//save items queue data
	size_t temp;
	temp = queue.GetCurSize();
	file.write(reinterpret_cast<char*>(&temp), sizeof(size_t)); //write size
	for (size_t i = 0; i < queue.GetCurSize(); i++)
	{
		queue.Get(i).SaveToFile(file);
	}
}

void BasicConveyorTile::DeserializeFromStream(std::istream& file)
{
	DirectedTile::DeserializeFromStream(file);
	size_t size;
	file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	for (size_t i = 0; i < size; i++)
	{
		queue.Push(ItemDescriptor::LoadFromFile(file));
	}
}

void BasicConveyorTile::DrawOver() const
{
	for (int i = 0; i < queue.GetCurSize(); i++)
	{
		const ItemDescriptor& p = queue.Get(i);
		if (p.item)
		{
			if (p.prog <= .5f)
			{
				switch (direction) {
				case Direction::WEST:
					p.item->Draw(xpos * 128 - 32 + p.prog * 128.f, ypos * 128 + 32, 64, 64);
					break;
				case Direction::EAST:
					p.item->Draw(xpos * 128 + 96 - p.prog * 128.f, ypos * 128 + 32, 64, 64);
					break;
				case Direction::SOUTH:
					p.item->Draw(xpos * 128 + 32, ypos * 128 + 96 - p.prog * 128.f, 64, 64);
					break;
				case Direction::NORTH:
					p.item->Draw(xpos * 128 + 32, ypos * 128 - 32 + p.prog * 128.f, 64, 64);
					break;
				}
			}
			else
			{
				switch (p.from) {
				case Direction::EAST:
					p.item->Draw(xpos * 128 - 32 + p.prog * 128.f, ypos * 128 + 32, 64, 64);
					break;
				case Direction::WEST:
					p.item->Draw(xpos * 128 + 96 - p.prog * 128.f, ypos * 128 + 32, 64, 64);
					break;
				case Direction::NORTH:
				case Direction::AETHER:
				default:
					p.item->Draw(xpos * 128 + 32, ypos * 128 + 96 - p.prog * 128.f, 64, 64);
					break;
				case Direction::SOUTH:
					p.item->Draw(xpos * 128 + 32, ypos * 128 - 32 + p.prog * 128.f, 64, 64);
					break;
				}
			}
		}
	}
}

const ItemBundle* BasicConveyorTile::GetMiningResult(Tool* tool) const
{
	return DROP->ConstCollapseToItemBundle();
}

void BasicConveyorTile::Init(nlohmann::json data)
{
	for (int i = 0; i < 16; i++)
		TEXTURES[i] = game_GetTexture(data[DATA_JSON_TEXTURE_LIST_KEY][i]);
	MINING_RESISTANCE = data[DATA_JSON_MINING_RESISTANCE_KEY];
	TOOL_TYPE = Tool::GetToolTypeFromString(data[DATA_JSON_TOOL_TYPE_KEY]);
	NAME = data[DATA_JSON_NAME_KEY];
	DROP = game_GetLootBundle(data[DATA_JSON_DROP_KEY]);
	CONVEYOR_ITEMS_DIST = data[DATA_JSON_CONVEYOR_ITEM_DISTANCE_KEY];
	CONVEYOR_SPEED = data[DATA_JSON_CONVEYOR_SPEED_KEY];
	CONVEYOR_MAX_ITEMS = data[DATA_JSON_CONVEYOR_MAX_ITEMS_KEY];
}

BasicConveyorTile::ItemDescriptor::ItemDescriptor(float p, Direction f, Item* i) : prog{ p }, from{ f }, item{ i }
{}

void BasicConveyorTile::ItemDescriptor::SaveToFile(std::ostream& file)
{
	file.write(reinterpret_cast<char*>(&prog), sizeof(float));
	uint8_t temp = from;
	file.write(reinterpret_cast<char*>(&temp), sizeof(uint8_t));
	Item::SaveToFile(item, file);
}

BasicConveyorTile::ItemDescriptor BasicConveyorTile::ItemDescriptor::LoadFromFile(std::istream& file)
{
	ItemDescriptor d;
	file.read(reinterpret_cast<char*>(&d.prog), sizeof(float));
	file.read(reinterpret_cast<char*>(&d.from), sizeof(uint8_t));
	d.item = Item::LoadFromFile(file);
	return d;
}
