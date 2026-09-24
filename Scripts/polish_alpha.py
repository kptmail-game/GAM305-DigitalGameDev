"""Add factory set dressing to the generated shared Alpha map, using engine meshes only."""
import unreal
world=unreal.EditorLoadingAndSavingUtils.load_map('/Game/Maps/AlphaIntegration')
actors=unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
tools=unreal.AssetToolsHelpers.get_asset_tools()
cube=unreal.load_asset('/Engine/BasicShapes/Cube')
cylinder=unreal.load_asset('/Engine/BasicShapes/Cylinder')
def mat(name,rgb):
    path='/Game/Alpha/'+name
    m=unreal.load_asset(path)
    if m: return m
    m=tools.create_asset(name,'/Game/Alpha',unreal.Material,unreal.MaterialFactoryNew())
    m.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_UNLIT)
    c=unreal.MaterialEditingLibrary.create_material_expression(m,unreal.MaterialExpressionConstant3Vector)
    c.set_editor_property('constant',unreal.LinearColor(*rgb,1))
    unreal.MaterialEditingLibrary.connect_material_property(c,'',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    unreal.MaterialEditingLibrary.recompile_material(m)
    unreal.EditorAssetLibrary.save_loaded_asset(m)
    return m
mats={n:mat(n,c) for n,c in {'M_Trim':(.05,.09,.12),'M_Pipe':(.16,.22,.25),'M_Light':(.3,.85,1),'M_Amber':(1,.57,.04),'M_White':(.7,.85,.85)}.items()}
textmat=unreal.load_asset('/Game/Alpha/M_SignText')
if not textmat:
    textmat=unreal.EditorAssetLibrary.duplicate_asset('/Engine/EngineMaterials/DefaultTextMaterialOpaque','/Game/Alpha/M_SignText')
textmat.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_UNLIT)
white=unreal.MaterialEditingLibrary.create_material_expression(textmat,unreal.MaterialExpressionConstant3Vector)
white.set_editor_property('constant',unreal.LinearColor(r=.9,g=.96,b=1,a=1))
unreal.MaterialEditingLibrary.connect_material_property(white,'',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
unreal.MaterialEditingLibrary.recompile_material(textmat)
unreal.EditorAssetLibrary.save_loaded_asset(textmat)
for a in actors.get_all_level_actors():
    if a.get_actor_label().startswith('Detail_'): actors.destroy_actor(a)
def prop(name,xyz,size,material='M_Trim',shape=None):
    a=actors.spawn_actor_from_class(unreal.StaticMeshActor,unreal.Vector(*xyz))
    a.set_actor_label('Detail_'+name)
    a.static_mesh_component.set_static_mesh(shape or cube)
    a.static_mesh_component.set_material(0,mats[material])
    a.set_actor_scale3d(unreal.Vector(*(v/100 for v in size)))
    a.set_actor_enable_collision(False)
    return a
def sign(text,xyz,size=38,color=(165,220,230,255)):
    a=actors.spawn_actor_from_class(unreal.TextRenderActor,unreal.Vector(*xyz),unreal.Rotator(pitch=0,yaw=90,roll=0))
    a.set_actor_label('Detail_Sign_'+text.replace('\n','_'))
    c=a.get_component_by_class(unreal.TextRenderComponent)
    c.set_text(text); c.set_world_size(size); c.set_text_render_color(unreal.Color(*color)); c.set_text_material(textmat)
for room,title in enumerate(['01 / INTAKE','02 / UTILITIES','03 / ASSEMBLY','04 / EMERGENCY POWER']):
    base=room*3000
    sign(title,(base+100,-260,460))
    for x in range(0,3000,300):
        prop('FloorJoint',(base+x,170,1),(8,120,4),'M_Trim')
    prop('FloorEdge',(base+1400,251,-20),(3000,12,25),'M_Trim')
    prop('UpperPipe',(base+1400,-250,370),(3000,35,35),'M_Pipe')
    for x in (500,1500,2450):
        prop('LampHousing',(base+x,-210,390),(180,55,40))
        prop('LampStrip',(base+x,-175,380),(140,12,10),'M_Light')
    for x in (300,600,2100):
        prop('StorageCrate',(base+x,-200,65),(135,95,130),'M_Pipe')
        prop('CrateBand',(base+x,-150,65),(20,8,130),'M_Trim')
    prop('Tank',(base+1200,-240,100),(140,120,200),'M_Pipe',cylinder)
    prop('TankBand',(base+1200,-172,120),(110,10,14),'M_Trim')
    prop('CellSocket',(base+2500,-40,96),(145,130,12),'M_Amber')
    for x in range(-100,101,40):
        prop('ObjectiveStripe',(base+2500+x,210,90),(20,12,25),'M_Amber')
    sign('CELL '+str(room+1)+' / 4',(base+2390,-100,365),32,(255,215,75,255))
prop('EntryBackdrop',(-750,-320,300),(1500,40,1400))
sign('MAINTENANCE UNIT 07',(40,-150,280),24)
sign('RESTORE EXIT POWER  >',(40,-150,225),24,(255,215,75,255))
for x in (11690,11910): prop('ExitFrame',(x,-10,155),(30,280,310),'M_Trim')
prop('ExitHeader',(11800,-10,320),(250,280,30),'M_Light')
sign('EMERGENCY EXIT',(11530,-120,390),36,(120,255,170,255))
for a in actors.get_all_level_actors():
    if isinstance(a,unreal.FactoryElement):
        a.get_component_by_class(unreal.TextRenderComponent).set_text_material(textmat)
        if a.get_editor_property('kind')==unreal.FactoryElementKind.CELL:
            a.configure(unreal.FactoryElementKind.CELL,unreal.Vector(95,110,115))
assert unreal.EditorLoadingAndSavingUtils.save_map(world,'/Game/Maps/AlphaIntegration')
unreal.log('ALPHA_POLISH_SAVED')
