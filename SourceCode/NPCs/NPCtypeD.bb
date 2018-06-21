Function InitializeNPCtypeD(n.NPCs)
    n\NVName = "Human"
    n\collider = CreatePivot()
    EntityRadius n\collider, 0.32
    EntityType n\collider, HIT_PLAYER

    Local n2.NPCs
	For n2 = Each NPCs
		If (n2\npcType = n\npcType And n2\obj <> 0) Then
			n\obj = CopyEntity(n2\obj)
			Exit
		EndIf
	Next
    
	If (n\obj = 0) Then
		n\obj = LoadAnimMesh("GFX/NPCs/classd/classd.b3d")
	EndIf
    
    temp# = 0.5 / MeshWidth(n\obj)
    ScaleEntity n\obj, temp, temp, temp
    
    n\Speed = 2.0 / 100
    
    MeshCullBox (n\obj, -MeshWidth(n\obj), -MeshHeight(n\obj), -MeshDepth(n\obj), MeshWidth(n\obj)*2, MeshHeight(n\obj)*2, MeshDepth(n\obj)*2)
End Function

Function UpdateNPCtypeD(n.NPCs)
    RotateEntity(n\collider, 0, EntityYaw(n\collider), EntityRoll(n\collider), True)
    
    prevFrame = AnimTime(n\obj)
    
    Select n\state
        Case 0 ;idle
            n\CurrSpeed = CurveValue(0.0, n\CurrSpeed, 5.0)
            Animate2(n\obj, AnimTime(n\obj), 210, 235, 0.1)
        Case 1 ;walking
            If n\state2 = 1.0 Then
                n\CurrSpeed = CurveValue(n\Speed*0.7, n\CurrSpeed, 20.0)
            Else
                n\CurrSpeed = CurveValue(0.015, n\CurrSpeed, 5.0)
            EndIf
            Animate2(n\obj, AnimTime(n\obj), 236, 260, n\CurrSpeed * 18)
        Case 2 ;running
            n\CurrSpeed = CurveValue(0.03, n\CurrSpeed, 5.0)
            Animate2(n\obj, AnimTime(n\obj), 301, 319, n\CurrSpeed * 18)
    End Select
    
    MoveEntity(n\collider, 0, 0, n\CurrSpeed * timing\tickDuration)
    
    PositionEntity(n\obj, EntityX(n\collider), EntityY(n\collider) - 0.32, EntityZ(n\collider))
    
    RotateEntity n\obj, EntityPitch(n\collider), EntityYaw(n\collider)-180.0, 0
End Function

;~IDEal Editor Parameters:
;~C#Blitz3D