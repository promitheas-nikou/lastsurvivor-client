#include "Item.h"
#include "ResourceLoader.h"
#include "World.h"
#include <allegro5/allegro_font.h>
#include "Config.h"
#include "SimpleItemBundle.h"

std::unordered_map<std::string, uint32_t> Item::str_to_id;
std::map<uint32_t, std::string> Item::id_to_str;

int Item::MLBUF = 0;

bool Item::DrawItemDetailsPaneMultilineCB(int line_num, const char* line, int size, void* extra)
{
    MLBUF = line_num;
    return true;
}

Item::Item(std::string n, std::string d) : name{ n }, description{ d }, amount{ 1 }
{}

int Item::GetMaxStackSize() const
{
    return 128;
}

std::string Item::GetName() const
{
    return name;
}

std::string Item::GetDescription() const
{
    return description;
}

int Item::GetAmount() const
{
    return amount;
}

int Item::RemoveAmount(int targetAmount)
{
    int removeAmount = std::min(targetAmount, amount);
    amount -= removeAmount;
    return removeAmount;
}

Item* Item::SetAmount(int a)
{
    amount = a;
    return this;
}

bool Item::Equals(const Item& item) const
{
    return Equals(&item);
}

bool Item::Equals(const Item* item) const
{
    if (item == nullptr)
        return false;
    return item->GetID()==GetID();
}

void Item::DrawItemDetailsPane(int x, int y)
{
    std::string id = ("#" + GetID());
    int w1 = al_get_text_width(loaded_fonts["default"][30], GetName().c_str());
    int w2 = al_get_text_width(loaded_fonts["default"][20], id.c_str());
    int w3 = al_get_text_width(loaded_fonts["default"][20],GetDescription().c_str());
    int w = std::max(300,std::max(w1+w2,w3/5));
    
    MLBUF = 0;
    al_do_multiline_text(loaded_fonts["default"][20], w, GetDescription().c_str(), &DrawItemDetailsPaneMultilineCB, NULL);
    int h = (MLBUF + 1) * 23 + 53;
    al_draw_filled_rectangle(x, y, x + w + 25, y + h, al_map_rgba(10, 30, 50, 200));
    al_draw_text(loaded_fonts["default"][30], al_map_rgba(255, 255, 255, 255), x + 10, y + 10, 0, GetName().c_str());
    al_draw_text(loaded_fonts["default"][20], al_map_rgba(150, 150, 150, 255), x + w1 + 15, y + 20, 0, id.c_str());
    al_draw_multiline_text(loaded_fonts["default"][20], al_map_rgba(255, 255, 255, 255), x + 10, y + 45, w, 23, 0, GetDescription().c_str());
}

ItemBundle* Item::ConstCollapseToItemBundle() const
{
    SimpleItemBundle* b = new SimpleItemBundle();
    b->AddItem(this->Clone());
    return b;
}

void Item::SaveToFile(std::ofstream &file)
{
    file.write(reinterpret_cast<char*>(&str_to_id[GetID()]), sizeof(uint32_t));
    uint32_t d = GetAmount();
    file.write(reinterpret_cast<char*>(&d), sizeof(int));
}

void Item::SaveToFile(Item* item, std::ofstream& file)
{
    constexpr uint32_t nullitemid = 0xFFFFFFFF;
    if (item == nullptr)
        file.write(reinterpret_cast<const char*>(&nullitemid), sizeof(uint32_t));
    else
        item->SaveToFile(file);
}

Item* Item::LoadFromFile(std::ifstream &file)
{
    uint32_t i;
    file.read(reinterpret_cast<char*>(&i), sizeof(uint32_t));
    if (i == 0xFFFFFFFF)
        return nullptr;
    int a;
    Item* item = MakeItemFromID(id_to_str[i]);
    file.read(reinterpret_cast<char*>(&a), sizeof(int));
    item->SetAmount(a);
    item->LoadAdditionalDataFromFile(file);
    return item;
}

void Item::LoadAdditionalDataFromFile(std::ifstream& file)
{}

void Item::AddConstToInventory(ItemInventory* inv) const
{
    inv->AddConstItem(this);
}

int Item::AddAmount(int a)
{
    amount += a;
    if (amount > GetMaxStackSize())
    {
        int tmp = amount - GetMaxStackSize();
        amount = GetMaxStackSize();
        return tmp;
    }
    return 0;
}

void Item::DrawText(int x, int y, ALLEGRO_FONT* font, ALLEGRO_COLOR color, int align) const
{
    al_draw_textf(font, color, x, y, align, "%d x %s", GetAmount(), GetName().c_str());
}

void Item::DrawWithText(int x, int y, int width, int height) const
{
    Draw(x, y, width, height);
    DrawText(x + width, y + width / 2 - 20, loaded_fonts["default"][30], gameconfig::SOLID_TEXT_COLOR_NORMAL, 0);
}

std::unordered_map<std::string, Item*> prototype_items;

Item* MakeItemFromID(std::string id)
{
    Item* p = prototype_items[id];
    return (p == nullptr) ? nullptr : p->Clone();
}

Item* MakeItemFromJSON(nlohmann::json data)
{
    Item* item = MakeItemFromID(data["id"]);
    if(item==nullptr)
        return nullptr;
    item->SetAmount(data["amount"]);
    return item;
}
