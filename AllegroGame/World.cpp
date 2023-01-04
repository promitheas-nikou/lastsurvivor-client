#include <fstream>
#include "zip.h"
#include "json.h"
#include "World.h"
#include "ResourceLoader.h"
#include "Graphics.h"
#include "dirent.h"
#include "MathUtils.h"
#include "SimplexNoise.h"
#include "DebugInfo.h"
#include <exception>
#include <iostream>

#define DEBUG


#define WORLD_SAVE_MANIFEST_FILENAME "world_manifest.json"
#define WORLD_SAVE_PLAYER_DATA_FILENAME "player.entitydata"
#define WORLD_SAVE_MANIFEST_DYNAMIC_WORLDGEN_KEY "DO_DYNAMIC_WORLDGEN"
#define WORLD_SAVE_MANIFEST_SEED_KEY "SEED"
#define WORLD_SAVE_MANIFEST_VERSION_KEY "VERSION"
#define WORLD_SAVE_MANIFEST_GAMETIME_KEY "GAMETIME"
#define WORLD_SAVE_MANIFEST_ABSOLUTETIME_KEY "ABSOLUTETIME"
#define WORLD_SAVE_MANIFEST_VER_MAJOR_KEY "VER_MAJOR"
#define WORLD_SAVE_MANIFEST_VER_MINOR_KEY "VER_MINOR"
#define WORLD_SAVE_MANIFEST_NAME_KEY "NAME"
#define WORLD_SAVE_MANIFEST_CHUNKS_KEY "CHUNKS"
#define WORLD_SAVE_MANIFEST_TILES_DICT_KEY "TILES"
#define WORLD_SAVE_MANIFEST_GROUND_TILES_DICT_KEY "GTILES"
#define WORLD_SAVE_MANIFEST_ENTITIES_DICT_KEY "ENTITIES"
#define WORLD_SAVE_MANIFEST_ITEMS_DICT_KEY "ITEMS"
#define WORLD_SAVE_MANIFEST_CHUNK_X_SIZE_KEY "CHUNK_X_SIZE"
#define WORLD_SAVE_MANIFEST_CHUNK_Y_SIZE_KEY "CHUNK_Y_SIZE"
#define WORLD_SAVE_MANIFEST_HAS_QUESTS_BOOL_KEY "HAS_QUESTS"
#define WORLD_SAVE_COORDINATE_DELIMETER "~"
#define WORLD_SAVE_CHUNKDATA_FILE_EXTENSION ".chunkdata"
#define WORLD_SAVE_ENTITYDATA_FILE_EXTENSION ".entitydata"
#define WORLD_SAVE_CHUNKDATA_DIR "chunks"
#define WORLD_SAVE_ENTITYDATA_DIR "entities"

ALLEGRO_BITMAP* World::nullTileBitmap;

ALLEGRO_COLOR CombineColors(ALLEGRO_COLOR x, ALLEGRO_COLOR y, float z)
{
    y.a *= z;
    x.a *= (1.f - z);
    float r = x.a * x.r + y.a * y.r;
    float b = x.a * x.b + y.a * y.b;
    float g = x.a * x.g + y.a * y.g;
    float a = x.a + y.a - x.a * y.a;
    return al_map_rgba_f(r, b, g, a);
}


ALLEGRO_COLOR World::CalcAmbientColor()
{
    constexpr ALLEGRO_COLOR MORNING_COLOR = { .r = .5f, .g = .4f, .b = .2f, .a = 1.f }; //00000 or 0 minutes
    constexpr ALLEGRO_COLOR NOON_COLOR = { .r = 1.f, .g = 1.f, .b = .8f, .a = 1.f }; //30000 or 10 minutes
    constexpr ALLEGRO_COLOR AFTERNOON_COLOR = { .r = .9f, .g = .85f, .b = .7f, .a = 1.f}; //48000 or 16 minutes
    constexpr ALLEGRO_COLOR NIGHT_COLOR = { .r = .2f, .g = .3f, .b = .25f, .a = 1.f }; //60000 or 20 minutes
    constexpr ALLEGRO_COLOR MIDNIGHT_COLOR = { .r = .075f, .g = .1f, .b = .2f, .a = 1.f }; //75000 or 25 minutes
    if (gametime < 30000)
        return CombineColors(MORNING_COLOR, NOON_COLOR, gametime / 30000.f);
    if (gametime < 48000)
        return CombineColors(NOON_COLOR, AFTERNOON_COLOR, (gametime - 30000) / 18000.f);
    if (gametime < 60000)
        return CombineColors(AFTERNOON_COLOR, NIGHT_COLOR, (gametime - 48000) / 12000.f);
    if (gametime < 75000)
        return CombineColors(NIGHT_COLOR, MIDNIGHT_COLOR, (gametime - 60000) / 15000.f);
    return CombineColors(MIDNIGHT_COLOR, MORNING_COLOR, (gametime - 75000) / 15000.f);

}

void World::UpdateEntityVector()
{
    std::vector<Entity*> new_entities;
    for (int i = 0; i < entities.size(); i++)
        if (!entities[i]->IsDead())
            new_entities.push_back(entities[i]);
    entityUpdates = 0;
    entities = new_entities;
}

GroundTile* World::GenerateGroundTile(int x, int y)
{
    if (GenerateGetLevelHeight(x, y) < .5)
    {
        if (GenerateGetLevelHeight(x, y) < -.4)
        {
            if (GenerateGetLevelHeight(x, y) < -.6)
            {
                return MakeGroundTile(this, "gtiles.water", x, y);
            }
            return MakeGroundTile(this, "gtiles.sand", x, y);
        }
        if (GenerateGetLevelTemperature(x, y) < .5)
        {
            if (GenerateGetLevelHumidity(x, y) < -.5)
                return MakeGroundTile(this, "gtiles.sand", x, y);
            else
                return MakeGroundTile(this, "gtiles.grass", x, y);
        }
        else
            return MakeGroundTile(this, "gtiles.dirt", x, y);
    }
    else if(GenerateGetLevelOreDensityFactor(x,y)>=.85f)
    {
        float o = GenerateGetLevelOreQualityFactor(x, y);
        if (o >= .8f)
            return MakeGroundTile(this, "gtiles.malachite_ore", x, y);
        else if (o <= .8f && o>= .6f)
            return MakeGroundTile(this, "gtiles.azurite_ore", x, y);
        else if (o <= .6f && o>= .3f)
            return MakeGroundTile(this, "gtiles.hematite_ore", x, y);
        else if (o <= .3f && o>= .1f)
            return MakeGroundTile(this, "gtiles.azurite_ore", x, y);
        else if (o <= .1f && o>= -.3f)
            return MakeGroundTile(this, "gtiles.stone", x, y);
        else if (o <= -.3f && o >= -.5f)
            return MakeGroundTile(this, "gtiles.magnetite_ore", x, y);
        else if (o <= -.5f && o >= -.8f)
            return MakeGroundTile(this, "gtiles.malachite_ore", x, y);
        else  if (o <= -.8f)
            return MakeGroundTile(this, "gtiles.stone", x, y);
    }
    else
        return MakeGroundTile(this, "gtiles.stone", x, y);
}

float World::GenerateGetLevelHeight(int x, int y)
{
    return randgen.fractal(3, x / 20.f, y / 20.f);
}

float World::GenerateGetLevelTemperature(int x, int y)
{
    return randgen.fractal(3, x / 100.f-812, y / 100.f+752);
}

float World::GenerateGetLevelHumidity(int x, int y)
{
    return randgen.fractal(3, x / 40.f + 925, y / 40.f - 461);
}

float World::GenerateGetLevelOreQualityFactor(int x, int y)
{
    return randgen.fractal(2, x / 50.f - 5125, y / 50.f - 742);
}

float World::GenerateGetLevelOreDensityFactor(int x, int y)
{
    return randgen.fractal(1, x / 20.f + 5125, y / 20.f - 7342);
}

float World::GenerateGetLevelTileRandomness(int x, int y)
{
    return randgen.fractal(5, x * 46.77335f + 925, y *843.91275f - 461);
}

Tile* World::GenerateTile(int x, int y)
{
    if (GenerateGetLevelHeight(x, y) < .5)
    {
        if (GenerateGetLevelHeight(x, y) < -.4)
        {
            if (GenerateGetLevelHeight(x, y) < -.6)
            {
                return MakeTile(this, "tiles.air", x, y);
            }
            return MakeTile(this, "tiles.air", x, y);
        }
        if (GenerateGetLevelTemperature(x, y) < .5)
        {
            if (GenerateGetLevelHumidity(x, y) < -.5)
                return MakeTile(this, "tiles.air", x, y);
            else if (GenerateGetLevelHumidity(x, y) < .4)
            {
                if(GenerateGetLevelTileRandomness(x,y)>.8)
                    return MakeTile(this, "tiles.berry_bush", x, y);
                else
                    return MakeTile(this, "tiles.air", x, y);
            }
            else
            {
                return MakeTile(this, "tiles.tree", x, y);
            }
        }
        else
            return MakeTile(this, "tiles.air", x, y);
    }
    else
        return MakeTile(this, "tiles.air", x, y);
}

double World::GetMeasuredTPS()
{
    return TPSmeasured;
}

WorldChunk* World::GetChunk(int x, int y)
{
    return chunks[y][x];
}

int World::GetGameTime() const
{
    return gametime;
}

uint64_t World::GetGameTimeAbsolute() const
{
    return timeAbsolute;
}

Tile* World::RemoveTile(int x, int y)
{
    int subX = positive_modulo(x, 16);
    int subY = positive_modulo(y, 16);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
        GenerateChunk(chunkX, chunkY);
    Tile* r = GetChunk(chunkX, chunkY)->RemoveTile(subX, subY);
    if(r->DoesTickUpdates())
        GetChunk(chunkX, chunkY)->RemoveTickingTile(r);
    TileUpdateAround(x, y);
    return r;
}

void World::AddEntity(Entity* e)
{
    if(e!=nullptr)
        entities.push_back(e);
}

void World::Tick()
{
    loadedChunkCount = 0;
    if(doTileTick)
        for (const std::pair<int, std::map<int, WorldChunk*>> &m : chunks)
            for (const std::pair<int, WorldChunk*>& wc : m.second)
            {
                wc.second->Tick();
                loadedChunkCount++;
            }

    if(doEntityTick)
        for (int i=0;i<entities.size();i++)
            if(entities[i]!=nullptr)
                if(!entities[i]->IsDead())
                    entities[i]->Tick();
    player->Tick();

    if (((timeAbsolute/16) % ENTITY_UPDATE_RATE)==0)
        UpdateEntityVector();
    gametime = (gametime + 1) % 90000;

    DebugInfo::ticksEnd.push(al_get_time());
    if (DebugInfo::ticksEnd.size() > DebugInfo::TICKS_RECORD_NUM)
        DebugInfo::ticksEnd.pop();
    if(DebugInfo::ticksEnd.size()>1)
        TPSmeasured = (19*TPSmeasured + (DebugInfo::TICKS_RECORD_NUM-1) / (DebugInfo::ticksEnd.back() - DebugInfo::ticksEnd.front()))/20;
    timeAbsolute+=16;
}

PlayerEntity* World::GetPlayer() const
{
    return player;
}

void World::GenerateChunk(int x, int y)
{
    //printf("Generating worldchunk %d:%d\n", x, y);
    chunks[y][x] = new WorldChunk(this, x, y);
}

GroundTile* World::GetGroundTile(int x, int y)
{
    int subX = positive_modulo(x,16);
    int subY = positive_modulo(y,16);
    int chunkX = (x-subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y-subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
    {
        if (doDynamicWorldGen)
            GenerateChunk(chunkX, chunkY);
        else
            return nullptr;
    }
    auto t = GetChunk(chunkX, chunkY)->GetGroundTile(subX, subY);
    return t;
}

GroundTile* World::SetGroundTile(GroundTile* gtile, int x, int y)
{
    int subX = positive_modulo(x, 16);
    int subY = positive_modulo(y, 16);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
    {
        if (doDynamicWorldGen)
            GenerateChunk(chunkX, chunkY);
        else
            return nullptr;
    }
    return GetChunk(chunkX, chunkY)->SetGroundTile(gtile,subX, subY);
}

Tile* World::GetTile(int x, int y)
{
    int subX = positive_modulo(x, WorldChunk::CHUNK_SIZE_X);
    int subY = positive_modulo(y, WorldChunk::CHUNK_SIZE_Y);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
    {
        if (doDynamicWorldGen)
            GenerateChunk(chunkX, chunkY);
        else
            return nullptr;
    }
    auto t = GetChunk(chunkX, chunkY)->GetTile(subX, subY);
    return t;
}

Tile* World::GetTileRelative(int x, int y, Direction d)
{
    switch (d)
    {
    case Direction::NORTH:
        return GetTile(x, y - 1);
    case Direction::SOUTH:
        return GetTile(x, y + 1);
    case Direction::EAST:
        return GetTile(x + 1, y);
    case Direction::WEST:
        return GetTile(x - 1, y);
    case Direction::UP:
    case Direction::DOWN:
    case Direction::AETHER:
    default:
        return nullptr;
    }
}

Tile* World::SetTile(Tile* tile, int x, int y)
{
    int subX = positive_modulo(x, 16);
    int subY = positive_modulo(y, 16);
    int chunkX = (x - subX) / WorldChunk::CHUNK_SIZE_X;
    int chunkY = (y - subY) / WorldChunk::CHUNK_SIZE_Y;
    if (!IsChunkGenerated(chunkX, chunkY))
    {
        if (doDynamicWorldGen)
            GenerateChunk(chunkX, chunkY);
        else
            return nullptr;
    }
    WorldChunk* c = GetChunk(chunkX, chunkY);
    Tile* r = c->SetTile(tile, subX, subY);
    if(tile->DoesTickUpdates())
        c->AddTickingTile(tile);
    if (r->DoesTickUpdates())
        c->RemoveTickingTile(r);
    TileUpdateAround(x, y);
    return r;
}

bool World::IsChunkGenerated(int x, int y)
{
    auto row = chunks.find(y);
    if (row == chunks.end())
        return false;
    return chunks[y].find(x) != chunks[y].end();
}

void World::TileUpdateAround(int x, int y)
{
    Tile* a;
    if ((a = GetTile(x, y)) != nullptr)
        a->TileUpdate();
    if ((a = GetTile(x-1, y)) != nullptr)
        a->TileUpdate();
    if ((a = GetTile(x, y+1)) != nullptr)
        a->TileUpdate();
    if ((a = GetTile(x+1, y)) != nullptr)
        a->TileUpdate();
    if ((a = GetTile(x, y-1)) != nullptr)
        a->TileUpdate();
}

Entity* World::GetEntityAtPos(float x, float y, Entity* ignore) const
{
    for (Entity* e : entities)
        if (e != ignore)
            if (e->ContainsPos(x, y))
                return e;
    if (player != ignore)
        if (player->ContainsPos(x, y))
                return player;
    return nullptr;
}

Entity* World::GetEntityColliding(Entity* entity, Entity* ignore) const
{
    for (Entity* e : entities)
        if (e != ignore)
            if (e->CollidesWith(entity))
                return e;
    if (player != ignore)
        if (player->CollidesWith(entity))
            return player;
    return nullptr;
}

std::vector<Entity*> World::GetEntitiesAtPos(float x, float y) const
{
    std::vector<Entity*> t;
    for (Entity* e : entities)
        if (e->ContainsPos(x, y))
            t.push_back(e);
    if(player->ContainsPos(x,y))
        t.push_back(player);
    return t;
}

std::vector<Entity*> World::GetEntitiesColliding(Entity* n) const
{
    std::vector<Entity*> t;
    for (Entity* e : entities)
    {
        if(n->CollidesWith(e))
            t.push_back(e);
    }
    if(player->CollidesWith(n))
        t.push_back(player);
    return t;
}
    
QuestCollection* World::GetQuestCollection() const
{
    return questCollection;
}

ALLEGRO_TRANSFORM draw_transform;

int OPTION_DRAW_TILES_LEFT = 12;
int OPTION_DRAW_TILES_RIGHT = 12;
int OPTION_DRAW_TILES_UP = 7;
int OPTION_DRAW_TILES_DOWN = 7;

std::vector<World::Light> LIGHTS;

void World::RegisterLight(Light l)
{
    LIGHTS.push_back(l);
}

void World::Draw()
{
    static float playerPos[3] = { 0.f, 0.f, 0.f };
    static float ambientLightColor[4] = { 1.f, 0.6f, 0.6f, 1.f };
    static float LIGHTS_POS[100][3];
    static float LIGHTS_BRIG[100];

    //DRAW TILES
    int offset_x = floor(player->GetXpos() * 128) - SCREEN_WIDTH / 2;
    int offset_y = floor(player->GetYpos() * 128) - SCREEN_HEIGHT / 2;
    int drawBeginX = floor(player->GetXpos()) - OPTION_DRAW_TILES_LEFT;
    int drawEndX = floor(player->GetXpos()) + OPTION_DRAW_TILES_RIGHT;
    int drawBeginY = floor(player->GetYpos()) - OPTION_DRAW_TILES_UP;
    int drawEndY = floor(player->GetYpos()) + OPTION_DRAW_TILES_DOWN;

    LIGHTS.clear();
    loaded_shaders["world"]->Use();
    Tile* tmpTile;
    GroundTile* tmpGTile;
    for (int x = drawBeginX-6; x < drawEndX+6; x++)
        for (int y = drawBeginY-6; y < drawEndY+6; y++)
            if ((tmpGTile = GetGroundTile(x, y)) != nullptr)
                tmpGTile->RegisterLights();

    for (int x = drawBeginX-6; x < drawEndX+6; x++)
        for (int y = drawBeginY-6; y < drawEndY+6; y++)
            if ((tmpTile = GetTile(x, y)) != nullptr)
                tmpTile->RegisterLights();
    for (int i = 0; i < LIGHTS.size(); i++)
    {
        LIGHTS_POS[i][0] = LIGHTS[i].GetXpos()*128 - offset_x;
        LIGHTS_POS[i][1] = -LIGHTS[i].GetYpos() * 128 + offset_y + SCREEN_HEIGHT;
        LIGHTS_POS[i][2] = 1.f;
        LIGHTS_BRIG[i] = LIGHTS[i].GetBrightness();
    }
    bool r;
    r = al_set_shader_float_vector("LIGHTS_POS", 3, (float*)LIGHTS_POS, LIGHTS.size());
    r = al_set_shader_float_vector("LIGHTS_BRIGHT", 1, (float*)LIGHTS_BRIG, LIGHTS.size());
    r = al_set_shader_int("LIGHTS_NUM", LIGHTS.size());


    playerPos[0] = offset_x;
    playerPos[1] = offset_y;
    ALLEGRO_COLOR ambientCol = CalcAmbientColor();
    ambientLightColor[0] = ambientCol.r;
    ambientLightColor[1] = ambientCol.g;
    ambientLightColor[2] = ambientCol.b;
    al_set_shader_float_vector("ambientLightColor", 4, ambientLightColor, 1);
    al_set_shader_float_vector("ambientLightColor", 4, ambientLightColor, 1);

    al_build_transform(&draw_transform, -offset_x, -offset_y, 1, 1, 0);
    al_use_transform(&draw_transform);
    //al_hold_bitmap_drawing(true);
    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            if ((tmpGTile = GetGroundTile(x, y)) != nullptr)
                tmpGTile->Draw();
            else
                al_draw_bitmap(nullTileBitmap, x * 128, y * 128, 0);

    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            if((tmpTile = GetTile(x, y)) != nullptr)
                tmpTile->Draw();
    for (int x = drawBeginX; x < drawEndX; x++)
        for (int y = drawBeginY; y < drawEndY; y++)
            if((tmpTile = GetTile(x, y)) != nullptr)
                tmpTile->DrawOver();
            //else nothing


    //DRAW ENTITIES 
    for (Entity* e : entities)
        if(!e->IsDead())
            e->Draw();
    player->Draw();
    al_hold_bitmap_drawing(false);
    if (player->showHitbox)
    {
        loaded_shaders["default"]->Use();
        al_draw_rectangle((player->GetXpos() - player->GetXsize() / 2) * 128, (player->GetYpos() - player->GetYsize() / 2) * 128, (player->GetXpos() + player->GetXsize() / 2) * 128, (player->GetYpos() + player->GetYsize() / 2) * 128, al_map_rgba(255, 255, 255, 255), 3.f);
        al_draw_line(player->GetXpos() * 128, player->GetYpos() * 128, player->GetXpos() * 128 - sinf(-player->GetRotation()) * 32, player->GetYpos() * 128 - cosf(-player->GetRotation()) * 32, al_map_rgba(0, 0, 255, 255), 4);
        for (Entity* e : entities)
        {
            al_draw_rectangle((e->GetXpos() - e->GetXsize() / 2) * 128, (e->GetYpos() - e->GetYsize() / 2) * 128, (e->GetXpos() + e->GetXsize() / 2) * 128, (e->GetYpos() + e->GetYsize() / 2) * 128, al_map_rgba(255, 255, 255, 255), 3.f);
            al_draw_line(e->GetXpos() * 128, e->GetYpos() * 128, e->GetXpos() * 128 - sinf(-e->GetRotation()) * 32, e->GetYpos() * 128 - cosf(-e->GetRotation()) * 32, al_map_rgba(0, 0, 255, 255), 4);
        }
        
    }
    al_build_transform(&draw_transform, 0, 0, 1, 1, 0);
    al_use_transform(&draw_transform);
}

//int OnWorldArchiveFileExtract() {}

World* World::LoadWorldFromFile(std::string filename)
{
    std::filesystem::path dir = std::filesystem::temp_directory_path() / "LastSurvivorTemp";
    World* world = nullptr;
#ifndef DEBUG
    try
    {
#endif //DEBUG
        zip_extract(filename.c_str(), dir.string().c_str(), NULL, NULL);
        std::ifstream manifestfilein(dir / WORLD_SAVE_MANIFEST_FILENAME);
        nlohmann::json manifest = nlohmann::json::parse(manifestfilein);
        manifestfilein.close();

        world = new World(
            manifest[WORLD_SAVE_MANIFEST_DYNAMIC_WORLDGEN_KEY],
            manifest[WORLD_SAVE_MANIFEST_SEED_KEY],
            manifest[WORLD_SAVE_MANIFEST_NAME_KEY],
            manifest[WORLD_SAVE_MANIFEST_VERSION_KEY],
            manifest[WORLD_SAVE_MANIFEST_VER_MAJOR_KEY],
            manifest[WORLD_SAVE_MANIFEST_VER_MINOR_KEY]);


        if (manifest.value(WORLD_SAVE_MANIFEST_HAS_QUESTS_BOOL_KEY,false))
        {
            std::ifstream questsjson(dir / "quests.json");
            world->questCollection = QuestCollection::LoadFromFile(questsjson);
            questsjson.close();
        }

        world->gametime = manifest[WORLD_SAVE_MANIFEST_GAMETIME_KEY];
        world->timeAbsolute = manifest[WORLD_SAVE_MANIFEST_ABSOLUTETIME_KEY];
        if ((manifest[WORLD_SAVE_MANIFEST_CHUNK_X_SIZE_KEY] != WorldChunk::CHUNK_SIZE_X) || (manifest[WORLD_SAVE_MANIFEST_CHUNK_Y_SIZE_KEY] != WorldChunk::CHUNK_SIZE_Y))
            throw std::format_error("WORLD FILE HAS DIFFERENT CHUNK SIZE!!!");
        std::map<uint32_t, std::string> cur_tile_keys;
        std::map<uint32_t, std::string> cur_gtile_keys;
        std::map<uint32_t, std::string> cur_item_ids;
        std::map<uint32_t, std::string> cur_entities_ids;

        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_TILES_DICT_KEY].items())
            cur_tile_keys[std::stoi(key)] = value;
        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_GROUND_TILES_DICT_KEY].items())
            cur_gtile_keys[std::stoi(key)] = value;
        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_ITEMS_DICT_KEY].items())
            cur_item_ids[std::stoi(key)] = value;
        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_ENTITIES_DICT_KEY].items())
            cur_entities_ids[std::stoi(key)] = value;
        Item::id_to_str = cur_item_ids;

        std::filesystem::path chunkdatadir = dir / WORLD_SAVE_CHUNKDATA_DIR;
        std::filesystem::path entitydatadir = dir / WORLD_SAVE_ENTITYDATA_DIR;

        for (auto& [key, value] : manifest[WORLD_SAVE_MANIFEST_CHUNKS_KEY].items())
        {
            int pos = key.find(WORLD_SAVE_COORDINATE_DELIMETER);
            int cx = std::stoi(key.substr(0, pos));
            int cy = std::stoi(key.substr(pos+1));
            WorldChunk* chunk = new WorldChunk(world, cx, cy, false);

            std::ifstream chunkdata = std::ifstream(chunkdatadir / (std::string)value, std::ios::binary);

            for (int y = 0; y < WorldChunk::CHUNK_SIZE_Y; y++)
                for (int x = 0; x < WorldChunk::CHUNK_SIZE_X; x++)
                {
                    uint32_t gtileid,tileid;
                    chunkdata.read(reinterpret_cast<char*>(&gtileid), sizeof(uint32_t));
                    chunk->GetGroundTileRef(x, y) = MakeGroundTile(world, cur_gtile_keys[gtileid], cx * WorldChunk::CHUNK_SIZE_Y + x, cy * WorldChunk::CHUNK_SIZE_X + y);
                    chunk->GetGroundTile(x, y)->LoadAdditionalDataFromFile(chunkdata);
                    chunkdata.read(reinterpret_cast<char*>(&tileid), sizeof(uint32_t));
                    chunk->GetTileRef(x, y) = MakeTile(world, cur_tile_keys[tileid], cx * WorldChunk::CHUNK_SIZE_Y + x, cy * WorldChunk::CHUNK_SIZE_X + y);
                    chunk->GetTile(x, y)->LoadAdditionalDataFromFile(chunkdata);
                    if (chunk->GetTile(x,y)->DoesTickUpdates())
                        chunk->AddTickingTile(chunk->GetTile(x,y));
                }
            chunkdata.close();
            world->chunks[cy][cx] = chunk;
        }



        std::ifstream playerdata(dir / "player" WORLD_SAVE_ENTITYDATA_FILE_EXTENSION, std::ios::binary);
        uint32_t pid;
        playerdata.read(reinterpret_cast<char*>(&pid), sizeof(uint32_t));
        world->player = dynamic_cast<PlayerEntity*>(MakeEntity(world, cur_entities_ids[pid], 0, 0));
        world->player->LoadAdditionalDataFromFile(playerdata);
        if(std::filesystem::exists(entitydatadir))
            for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(entitydatadir))
            {
                uint32_t eid;
                std::ifstream entitydata(entry, std::ios::binary);
                entitydata.read(reinterpret_cast<char*>(&eid), sizeof(uint32_t));
                Entity* e = MakeEntity(world, cur_entities_ids[eid], 0, 0);
                e->LoadAdditionalDataFromFile(entitydata);
                world->AddEntity(e);
                entitydata.close();
            }

        playerdata.close();

#ifndef DEBUG
    }
    catch (std::exception e)
    {
        printf("ERROR LOADING WORLD FROM FILE \"%s\"!\nDETAILS:\n%s\n", filename.c_str(),e.what());
        
        if (world != nullptr)
            delete world;
        world = nullptr;
    }
#endif //DEBUG
    std::filesystem::remove_all(dir);
    return world;
}

int begin_filename_index;

void zip_walk(struct zip_t* zip, const char* path) {
    DIR* dir;
    struct dirent* entry;
    char fullpath[MAX_PATH];
    struct stat s;

    memset(fullpath, 0, MAX_PATH);
    dir = opendir(path);
    assert(dir);

    while ((entry = readdir(dir))) {
        // skip "." and ".."
        if (!strcmp(entry->d_name, ".\0") || !strcmp(entry->d_name, "..\0"))
            continue;

        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
        stat(fullpath, &s);
        if (S_ISDIR(s.st_mode))
            zip_walk(zip, fullpath);
        else {
            zip_entry_open(zip, fullpath+begin_filename_index);
            zip_entry_fwrite(zip, fullpath);
            zip_entry_close(zip);
        }
    }

    closedir(dir);
}

void World::SaveToFile(std::string filename)
{
    std::filesystem::path dir = std::filesystem::temp_directory_path() / "LastSurvivorTemp";
    std::filesystem::create_directory(dir);
    std::cout << dir;
    std::ofstream manif_file(dir / WORLD_SAVE_MANIFEST_FILENAME);
    nlohmann::json manifest;
    manifest[WORLD_SAVE_MANIFEST_NAME_KEY] = worldname;
    manifest[WORLD_SAVE_MANIFEST_CHUNK_X_SIZE_KEY] = WorldChunk::CHUNK_SIZE_X;
    manifest[WORLD_SAVE_MANIFEST_CHUNK_Y_SIZE_KEY] = WorldChunk::CHUNK_SIZE_Y;
    manifest[WORLD_SAVE_MANIFEST_VERSION_KEY] = game_version_name;
    manifest[WORLD_SAVE_MANIFEST_VER_MAJOR_KEY] = game_version_major;
    manifest[WORLD_SAVE_MANIFEST_VER_MINOR_KEY] = game_version_minor;
    manifest[WORLD_SAVE_MANIFEST_DYNAMIC_WORLDGEN_KEY] = doDynamicWorldGen;
    manifest[WORLD_SAVE_MANIFEST_SEED_KEY] = SEED;
    manifest[WORLD_SAVE_MANIFEST_GAMETIME_KEY] = gametime;
    manifest[WORLD_SAVE_MANIFEST_ABSOLUTETIME_KEY] = timeAbsolute;
    manifest[WORLD_SAVE_MANIFEST_CHUNKS_KEY] = nlohmann::json::object();
    manifest[WORLD_SAVE_MANIFEST_HAS_QUESTS_BOOL_KEY] = GetQuestCollection() != nullptr;
    if (GetQuestCollection() != nullptr)
    {
        std::ofstream questsjson(dir/"quests.json");
        GetQuestCollection()->SaveToFile(questsjson);
        questsjson.flush();
        questsjson.close();
    }
    for (const std::pair<int, std::string>& p : item_ids_to_keys)
        manifest[WORLD_SAVE_MANIFEST_ITEMS_DICT_KEY][p.first] = p.second;
    for (const std::pair<int, std::string>& p : tile_ids_to_keys)
        manifest[WORLD_SAVE_MANIFEST_TILES_DICT_KEY][p.first] = p.second;
    for (const std::pair<int, std::string>& p : gtile_ids_to_keys)
        manifest[WORLD_SAVE_MANIFEST_GROUND_TILES_DICT_KEY][p.first] = p.second;
    for (const std::pair<int, std::string>& p : entity_ids_to_keys)
        manifest[WORLD_SAVE_MANIFEST_ENTITIES_DICT_KEY][p.first] = p.second;
    Item::str_to_id = item_keys_to_ids;
    std::filesystem::path chunkdatadir = dir / WORLD_SAVE_CHUNKDATA_DIR;
    std::filesystem::create_directory(chunkdatadir);
    std::filesystem::path entitydatadir = dir / WORLD_SAVE_ENTITYDATA_DIR;
    std::filesystem::create_directory(entitydatadir);
        for(const std::pair<int,std::map<int,WorldChunk*>>& p1: chunks)
        for (const std::pair<int, WorldChunk*>& p2 : p1.second)
        {
            std::string key = std::format("{}" WORLD_SAVE_COORDINATE_DELIMETER "{}", p2.first, p1.first);
            std::string filename = key + WORLD_SAVE_CHUNKDATA_FILE_EXTENSION;
            manifest[WORLD_SAVE_MANIFEST_CHUNKS_KEY][key] = filename;
            std::ofstream chunkdata(chunkdatadir / filename, std::ios::binary);
            for (int y = 0; y < WorldChunk::CHUNK_SIZE_Y; y++)
                for (int x = 0; x < WorldChunk::CHUNK_SIZE_X; x++)
                {
                    GroundTile* gt = p2.second->GetGroundTile(x,y);
                    chunkdata.write(reinterpret_cast<char*>(&gtile_keys_to_ids[gt->GetID()]), sizeof(uint32_t));
                    gt->WriteAdditionalDataToFile(chunkdata);
                    Tile* t = p2.second->GetTile(x, y);
                    chunkdata.write(reinterpret_cast<char*>(&tile_keys_to_ids[t->GetID()]), sizeof(uint32_t));
                    t->WriteAdditionalDataToFile(chunkdata);
                }
            chunkdata.flush();
            chunkdata.close();
        }
    manif_file << manifest;
    manif_file.flush();
    manif_file.close();

    std::ofstream playerdata(dir / "player" WORLD_SAVE_ENTITYDATA_FILE_EXTENSION, std::ios::binary);
    
    playerdata.write(reinterpret_cast<char*>(&entity_keys_to_ids[player->GetID()]), sizeof(uint32_t));
    player->WriteAdditionalDataToFile(playerdata);
    playerdata.flush();
    playerdata.close();

    int counter = 0;
    for (Entity* e : entities)
    {
        std::ofstream entitydatafile(entitydatadir / std::format("{}" WORLD_SAVE_ENTITYDATA_FILE_EXTENSION, counter++), std::ios::binary);
        entitydatafile.write(reinterpret_cast<char*>(&entity_keys_to_ids[e->GetID()]), sizeof(uint32_t));
        e->WriteAdditionalDataToFile(entitydatafile);
        entitydatafile.flush();
        entitydatafile.close();
    }
    
    zip_t* z = zip_open(filename.c_str(), ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    if (z == NULL)
    {
        std::cerr << "ERROR SAVING WORLD!!!\n";
        //std::cerr << mz_lat
        return;
    }
    begin_filename_index = dir.string().size()+1;
    zip_walk(z, dir.string().c_str());
    zip_close(z);
    try {
        std::filesystem::remove_all(dir);
    }
    catch (std::exception e)
    {
        std::cout << e.what();
    }
}

void World::Init()
{
    nullTileBitmap = loaded_bitmaps["tex.tiles.null"];
}

#include "CactusBossEntity.h"
#include "ZombieEntity.h"

World* World::CreateNewWorld(std::string name, uint64_t seed, std::function<void(int curx, int cury, int p, int t)> update)
{
    World* w = new World(true, seed, name, game_version_name, game_version_minor, game_version_major);
    w->GenerateChunk(0, 0);
    w->questCollection = QuestCollection::MakeNewCollection();
    w->player = new PlayerEntity(w, 0, 0);
    return w;
}

World* World::CreateNewFixedSizeWorld(std::string name, uint64_t seed, int minChunkX, int minChunkY, int maxChunkX, int maxChunkY, std::function<void(int curx, int cury, int p, int t)> update)
{
    World* w = new World(false, seed, name, game_version_name, game_version_minor, game_version_major);
    int c = 0;
    int t = (maxChunkY - minChunkY + 1) * (maxChunkX - minChunkX + 1);
    for (int y = minChunkY; y <= maxChunkY; y++)
        for (int x = minChunkX; x <= maxChunkX; x++)
        {
            w->GenerateChunk(x, y);
            update(x, y, c, t);
            c++;
        }
    w->player = new PlayerEntity(w, 0, 0);
    return w;
}


World::World(bool w, const uint64_t s, std::string name, std::string n, int min, int maj) : doDynamicWorldGen(w), entityUpdates{ 0 }, loadedChunkCount{ 0 }, SEED{ s }, WorldGameVersionName{ n }, WorldGameVersionMinor{ min }, WorldGameVersionMajor{ maj }, worldname{ name }
{
    srand(s);
    float a = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f));
    float b = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f));
    float c = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.f));
    float d = 1/c;

    std::cout << a << '\n' << b << '\n' << c << '\n' << d << '\n';
    randgen = SimplexNoise::SimplexNoise(a, b, c, d);
}

World::Light::Light(float x, float y, float b) : xpos{ x }, ypos{ y }, brightness{ b }
{
}

float World::Light::GetXpos() const
{
    return xpos;
}

float World::Light::GetYpos() const
{
    return ypos;
}

float World::Light::GetBrightness() const
{
    return brightness;
}

