Function FillRoom_hll_lshape_2(r.Rooms)
    Local d.Doors, d2.Doors, sc.SecurityCams, de.Decals, r2.Rooms, sc2.SecurityCams
    Local it.Items, i%
    Local xtemp%, ytemp%, ztemp%

    Local t1;, Bump

    r\objects[6] = CreatePivot()
    PositionEntity(r\objects[6], r\x + 640.0 * RoomScale, 8.0 * RoomScale, r\z - 896.0 * RoomScale)
    EntityParent(r\objects[6], r\obj)
End Function
