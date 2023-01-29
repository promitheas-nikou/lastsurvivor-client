#pragma once
#include <stdint.h>
#include <string>

typedef std::string game_String_t;


typedef uint32_t game_texID_t;
typedef uint32_t game_strID_t;
typedef uint32_t game_entityID_t;
typedef uint32_t game_itemID_t;
typedef uint32_t game_tileID_t;
typedef uint32_t game_gtileID_t;

typedef game_String_t game_texKey_t;
typedef game_String_t game_strKey_t;
typedef game_String_t game_entityKey_t;
typedef game_String_t game_itemKey_t;
typedef game_String_t game_tileKey_t;
typedef game_String_t game_gtileKey_t;

game_texID_t game_GetTextureIDFromKey(game_texKey_t key);
game_strID_t game_GetStringIDFromKey(game_strKey_t key);
game_itemID_t game_GetItemIDFromKey(game_itemKey_t key);
game_tileID_t game_GetTileIDFromKey(game_tileKey_t key);
game_gtileID_t game_GetGroundTileIDFromKey(game_gtileKey_t key);
game_entityID_t game_GetEntityIDFromKey(game_entityKey_t key);

game_texKey_t game_GetTextureKeyFromID(game_texID_t id);
game_strKey_t game_GetStringKeyFromID(game_strID_t id);
game_itemKey_t game_GetItemKeyFromID(game_itemID_t id);
game_tileKey_t game_GetTileKeyFromID(game_tileID_t id);
game_gtileKey_t game_GetGroundTileKeyFromID(game_gtileID_t id);
game_entityKey_t game_GetEntityKeyFromID(game_entityID_t id);
