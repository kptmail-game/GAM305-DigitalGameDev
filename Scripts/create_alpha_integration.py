"""Generate a separate integration map; never edits the Week 3 map or team maps."""
import unreal

world=unreal.EditorLoadingAndSavingUtils.new_blank_map(False)
actors=unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
tools=unreal.AssetToolsHelpers.get_asset_tools()
cube=unreal.load_asset('/Engine/BasicShapes/Cube')
unreal.EditorAssetLibrary.make_directory('/Game/Alpha')

def material(name,rgb):
    mat=unreal.load_asset('/Game/Alpha/'+name)
    if mat: return mat
    mat=tools.create_asset(name,'/Game/Alpha',unreal.Material,unreal.MaterialFactoryNew())
    mat.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_UNLIT)
    color=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionConstant3Vector)
    color.set_editor_property('constant',unreal.LinearColor(*rgb,1))
    normal=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionVertexNormalWS)
    direction=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionConstant3Vector)
    direction.set_editor_property('constant',unreal.LinearColor(-.6,.3,.7416,1))
    dot=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionDotProduct)
    unreal.MaterialEditingLibrary.connect_material_expressions(normal,'',dot,'A')
    unreal.MaterialEditingLibrary.connect_material_expressions(direction,'',dot,'B')
    mul=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionMultiply); mul.set_editor_property('const_b',.35)
    unreal.MaterialEditingLibrary.connect_material_expressions(dot,'',mul,'A')
    add=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionAdd); add.set_editor_property('const_b',.65)
    unreal.MaterialEditingLibrary.connect_material_expressions(mul,'',add,'A')
    final=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionMultiply)
    unreal.MaterialEditingLibrary.connect_material_expressions(color,'',final,'A'); unreal.MaterialEditingLibrary.connect_material_expressions(add,'',final,'B')
    unreal.MaterialEditingLibrary.connect_material_property(final,'',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    unreal.MaterialEditingLibrary.recompile_material(mat); unreal.EditorAssetLibrary.save_loaded_asset(mat)
    return mat

mats={name:material(name,rgb) for name,rgb in {'M_Cell':(1,.75,.06),'M_Green':(.12,.85,.32),'M_Blue':(.12,.6,1),'M_Purple':(.7,.25,1),'M_Hazard':(.95,.12,.07),'M_Slow':(.65,.42,.1),'M_Floor':(.12,.32,.4),'M_Back':(.025,.04,.07)}.items()}

def block(name,xyz,size,mat='M_Floor',collision=True):
    a=actors.spawn_actor_from_class(unreal.StaticMeshActor,unreal.Vector(*xyz)); a.set_actor_label(name)
    a.static_mesh_component.set_static_mesh(cube); a.static_mesh_component.set_material(0,mats[mat]); a.set_actor_scale3d(unreal.Vector(*(v/100 for v in size)))
    if not collision: a.set_actor_enable_collision(False)
    return a

def element(name,kind,xyz,size=(60,80,60)):
    a=actors.spawn_actor_from_class(unreal.FactoryElement,unreal.Vector(*xyz)); a.set_actor_label(name)
    a.configure(kind,unreal.Vector(*size)); return a

# Four compact test bays keep every feature available for team integration testing.
# This is deliberately not the final 5-10 minute factory route.
for room in range(4):
    base=room*3000
    block('BayFloor'+str(room),(base+1400,0,-50),(3000,500,100))
    block('BayBackdrop'+str(room),(base+1400,-320,300),(3000,40,1400),'M_Back',False)
    for x in (100,950,1900,2850):
        block('FactoryColumn',(base+x,-230,250),(50,50,500),'M_Floor',False)
    block('CellStep',(base+2500,0,45),(240,400,90))
    element('PowerCell'+str(room+1),unreal.FactoryElementKind.CELL,(base+2500,0,155))
    element('Repair'+str(room),unreal.FactoryElementKind.HEALTH,(base+2750,0,60))

element('Spikes',unreal.FactoryElementKind.SPIKES,(900,0,25),(120,220,50))
element('Shield',unreal.FactoryElementKind.SHIELD,(1500,0,60))
element('ElectricalPanel',unreal.FactoryElementKind.ELECTRICAL,(1850,0,55),(100,200,110))
element('SteamVent',unreal.FactoryElementKind.STEAM,(3800,0,70),(130,220,140))
element('Speed',unreal.FactoryElementKind.SPEED,(4300,0,60))
element('SlowingFloor',unreal.FactoryElementKind.SLOW_FLOOR,(4800,0,10),(450,220,25))
element('SlidingPress',unreal.FactoryElementKind.PRESS,(6800,0,80),(140,220,160))
element('SwingArm',unreal.FactoryElementKind.SWING_ARM,(8000,0,80),(90,220,160))
element('MovingBarrier',unreal.FactoryElementKind.MOVING_BARRIER,(9800,0,80),(65,220,160))
element('Exit',unreal.FactoryElementKind.EXIT,(11800,0,140),(120,250,280))
block('LeftBoundary',(-140,0,250),(50,500,500))
block('RightBoundary',(12000,0,250),(50,500,500))
actors.spawn_actor_from_class(unreal.PlayerStart,unreal.Vector(0,0,100))
assert unreal.EditorLoadingAndSavingUtils.save_map(world,'/Game/Maps/AlphaIntegration')
unreal.log('ALPHA_INTEGRATION_MAP_CREATED')
