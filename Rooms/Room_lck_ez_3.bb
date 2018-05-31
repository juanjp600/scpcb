Function FillRoom_lck_ez_3(r.Rooms)
    Local d.Doors, d2.Doors, sc.SecurityCams, de.Decals, r2.Rooms, sc2.SecurityCams
    Local it.Items, i%
    Local xtemp%, ytemp%, ztemp%
    
    Local t1;, Bump

    d = CreateDoor(r\zone, r\x - 728.0 * RoomScale, 0.0, r\z - 458.0 * RoomScale, 0, r, False, False, 3)
    d\AutoClose = False	: d\open = False  : d\locked = False
    
    d = CreateDoor(r\zone, r\x - 223.0 * RoomScale, 0.0, r\z - 736.0 * RoomScale, -90, r, False, False, 3)
    d\AutoClose = False	: d\open = False  : d\locked = False
    
    r\RoomDoors[0] = CreateDoor(r\zone, r\x - 459.0 * RoomScale, 0.0, r\z + 339.0 * RoomScale, 90, r, False, False)
    PositionEntity(r\RoomDoors[0]\buttons[0], r\x + 580.822 * RoomScale, EntityY(r\RoomDoors[0]\buttons[0],True), r\z - 606.679 * RoomScale, True)	
    PositionEntity(r\RoomDoors[0]\buttons[1], r\x + 580.822 * RoomScale, EntityY(r\RoomDoors[0]\buttons[1],True), r\z - 606.679 * RoomScale, True)
    r\RoomDoors[0]\dir = 0 : r\RoomDoors[0]\AutoClose = False	: r\RoomDoors[0]\open = True  : r\RoomDoors[0]\locked = True	
    r\RoomDoors[0]\MTFClose = False
    
    r\RoomDoors[1] = CreateDoor(r\zone, r\x + 385.0 * RoomScale, 0.0, r\z + 339.0 * RoomScale, 270, r, False, False)
    PositionEntity(r\RoomDoors[1]\buttons[0], r\x + 580.822 * RoomScale, EntityY(r\RoomDoors[1]\buttons[0],True), r\z - 606.679 * RoomScale, True)	
    PositionEntity(r\RoomDoors[1]\buttons[1], r\x + 580.822 * RoomScale, EntityY(r\RoomDoors[1]\buttons[1],True), r\z - 606.679 * RoomScale, True)
    r\RoomDoors[1]\dir = 0 : r\RoomDoors[1]\AutoClose = False	: r\RoomDoors[1]\open = True  : r\RoomDoors[1]\locked = True
    r\RoomDoors[1]\MTFClose = False
    FreeEntity r\RoomDoors[1]\obj2 : r\RoomDoors[1]\obj2 = 0
    
    r\Objects[0] = CreatePivot()
    PositionEntity r\Objects[0],r\x-48.0*RoomScale,128.0*RoomScale,r\z+320.0*RoomScale
    EntityParent r\Objects[0],r\obj
    
    For r2.Rooms = Each Rooms
        If r2<>r Then
            If r2\RoomTemplate\Name = "room3gw" Then
                r\Objects[3] = CopyEntity(r2\Objects[3],r\obj) ;don't load the mesh again
                Exit
            EndIf
        EndIf
    Next
    If r\Objects[3]=0 Then r\Objects[3] = LoadMesh("GFX/map/room3gw_pipes.b3d",r\obj)
    EntityPickMode r\Objects[3],2
End Function
