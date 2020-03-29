# Lua API: Item

## Example

```lua
mod:item {
	id = "myitem",    -- mandatory
	name = "My Item", -- mandatory
	tiles = "myitem.png",
}
```

## Attributes

### `groups`

Groups of the item. They can be used in recipes, and can also filter Lua-defined inventory widgets.

Each group must be set to `1` if present. Default value for each group is `0`, and it cannot exceeds `65535`.

Example:
```lua
groups = {
	om_fuel = 200 -- example burn time for a coal item
}
```

Engine groups always start with `om_` prefix. If you create your own groups, please prefix them with something to let people know that the group comes from your mod.

Available engine groups:

- `om_fuel`: used in `default:furnace` and `MouseWidgetItem`, the value represents the burn time

### `harvest_capability`

For a tool, set which blocks are easier to mine.

**Note:** This attribute would need more doc but it'll probably get removed soon.

### `id`

ID of the item. **Mandatory field.**

Example:
```lua
id = "stick"
```

IDs are usually of the form `mod:item` but the `mod:` prefix is prepended automatically so it's not needed.

### `mining_speed`

For a tool, speed at which it mines the block.

Example:
```lua
mining_speed = 1 -- this is the default value
```

### `name`

Label of the item. **Mandatory field.**

Example:
```lua
name = "Stick"
```

This label is the name that will appear everywhere in the game.

### `tiles`

Texture of the item.

Example:
``` lua
tiles = "myblock.png"
```

The textures will be loaded from `mods/<your-mod>/textures/items`

**Note:** Currently, you can only use textures of the exact same size (16x16, 32x32) than the other block/item textures in the game.

