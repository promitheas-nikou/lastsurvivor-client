io.write("Item Name: ")
itemName = io.read('*l')
io.write("Class Name: ")
classname = io.read('*l')
io.write("ID: ")
itemID = io.read('*l')
io.write("Texture: ")
texture = io.read('*l')
io.write("Drop: ")
drop = io.read('*l')
io.write("Description: ")
description = io.read('*l')

function interp(s, tab)
  return (s:gsub('($%b{})', function(w) return tab[w:sub(3, -2)] or w end))
end

header = io.open(classname..'.h','w')
code = io.open(classname..'.cpp','w')

header:write(
	interp(
		[[#pragma once

		#include "Item.h"

		class ${classname} :
			public Item
		{
		private:
			static std::string NAME;
			static std::string DESCRIPTION;
			static ALLEGRO_BITMAP* TEXTURE;

		public:

			static const std::string ID;

			std::string GetID() const final;

			${classname}();

			virtual Item* Clone() const override;

			void Draw(int x, int y, int width, int height) const final;

			static void Init(nlohmann::json data);

			virtual ~${}() = default;

		};

		]],
	_G)
)
header:flush()
header:close()

code:write(
	interp(
		[[#include "${classname}.h"
		#include "ResourceLoader.h"

		std::string ${classname}::NAME;
		std::string ${classname}::DESCRIPTION;
		ALLEGRO_BITMAP* ${classname}::TEXTURE;
		const std::string ${classname}::ID = "${itemID}";

		std::string ${classname}::GetID() const
		{
			return ID;
		}

		${classname}::${classname}(): Item(NAME, DESCRIPTION)
		{}

		Item* ${classname}::Clone() const
		{
			return new ${classname}(*this);
		}

		void ${classname}::Draw(int x, int y, int width, int height) const
		{
			al_draw_scaled_bitmap(TEXTURE, 0, 0, al_get_bitmap_width(TEXTURE), al_get_bitmap_height(TEXTURE), x, y, width, height, 0);
			al_draw_textf(loaded_fonts["default"][30], al_map_rgb(255, 0, 0), x + width - 40, y + height - 40, 0, "%d", GetAmount());
		}

		void ${classname}::Init(nlohmann::json data)
		{
			NAME = data[DATA_JSON_NAME_KEY];
			DESCRIPTION = data[DATA_JSON_DESCRIPTION_KEY];
			TEXTURE = loaded_bitmaps[data[DATA_JSON_TEXTURE_KEY]\];
		}

		]],
	_G)
)

print(
	interp(
		[[,
    {
      "id": "${itemID}",
      "name": "${itemName}",
      "description": "${description}",
      "texture": "tex.items.${itemID}"
    }]],
	_G)
)