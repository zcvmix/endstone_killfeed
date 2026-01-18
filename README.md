# Killfeed Plugin

Broadcasts custom death messages when players die.

## Install

Copy `endstone_killfeed.dll` (Windows) or `endstone_killfeed.so` (Linux) to your server's `plugins` folder.

## Config

First run creates `plugins/killfeed/messages.txt`:

```
# Use {user} for player name
# Lines with # are ignored

§l§e{user}§r §cjust got reality-checked by PvP.
§l§e{user}§r §cconfused confidence with skill.
```

Add more messages, one per line. Use `{user}` where the player's name should appear.

## Command

`/killfeed reload` - Reload config (operator only)

## Color Codes
Support all Colors

- `§l` = Bold
- `§e` = Yellow
- `§c` = Red
- `§a` = Green
- `§r` = Reset
