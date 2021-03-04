BomberTank is simple 2D tiling Game

![gameplay](https://github.com/xellzul/BomberTank/blob/master/examples/bomberman1.jpg?raw=true)

Exmaple usage:
```bash
make
./hlavaadr ./examples/assets/ ./examples/maps/bomberman 
```

You can create / edit existing maps, the format is:

```WIDTH <WHITESPACE> HEIGHT <WHITESPACE> (WIDTH*HEIGHT times)(ID <WHITESPACE>)```

Where WIDTH and HEIGHT are sizes of map, ID is either moving Entity or Static Tile

For example:
```
///START OF FILE
4 5
1 1 1 1
1 2 0 1
1 0 0 1
1 0 3 1
1 1 1 1
///END OF FILE
```

Possible IDs:
    0 - Air
    1 - Indestructible tile
    2 - Player Tank (depending on the mode)
    3 - Destructible tile
    4 - Computer Tank
    5 - Bonus box


Possible assets:
```(Air = 1, TankUp = 2, TankLeft = 3, TankDown = 4, TankRight = 5, Bricks = 6,
Explosion1 = 7, Explosion2 = 8, Explosion3 = 9, Explosion4 = 10, Steel = 11,
Ammo = 12, Crate = 13, Projectile = 14, Health = 15, Speed = 16, Repair = 17)```

how-to-use:
    install libsdl2 and libsdl2-image
        
        debian: ```sudo apt-get install libsdl2-2.0.0 libsdl2-image-2.0-0```
