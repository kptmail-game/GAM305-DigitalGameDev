"""Small procedural surface pass; preserves teammate assets and gameplay collision."""
import unreal
world = unreal.EditorLoadingAndSavingUtils.load_map('/Game/Maps/BetaIntegration')
tools = unreal.AssetToolsHelpers.get_asset_tools()
lib = unreal.MaterialEditingLibrary
unreal.EditorAssetLibrary.make_directory('/Game/Final')

def material(name, rgb, strength):
    path = '/Game/Final/' + name
    m = unreal.load_asset(path)
    if m:
        lib.delete_all_material_expressions(m)
    else:
        m = tools.create_asset(name, '/Game/Final', unreal.Material, unreal.MaterialFactoryNew())
    m.set_editor_property('shading_model', unreal.MaterialShadingModel.MSM_UNLIT)
    def node(cls): return lib.create_material_expression(m, cls)
    def wire(a, b, pin): lib.connect_material_expressions(a, '', b, pin)
    color = node(unreal.MaterialExpressionConstant3Vector)
    color.constant = unreal.LinearColor(*rgb, 1)
    uv = node(unreal.MaterialExpressionTextureCoordinate)
    uv.set_editor_property('u_tiling', 12)
    uv.set_editor_property('v_tiling', 12)
    mask = node(unreal.MaterialExpressionComponentMask)
    mask.set_editor_property('r', True)
    mask.set_editor_property('g', False)
    wire(uv, mask, '')
    sine = node(unreal.MaterialExpressionSine); wire(mask, sine, '')
    grain = node(unreal.MaterialExpressionMultiply)
    grain.set_editor_property('const_b', strength); wire(sine, grain, 'A')
    base = node(unreal.MaterialExpressionAdd)
    base.set_editor_property('const_b', .9); wire(grain, base, 'A')
    normal = node(unreal.MaterialExpressionVertexNormalWS)
    direction = node(unreal.MaterialExpressionConstant3Vector)
    direction.constant = unreal.LinearColor(-.45, .35, .82, 1)
    dot = node(unreal.MaterialExpressionDotProduct); wire(normal, dot, 'A'); wire(direction, dot, 'B')
    contrast = node(unreal.MaterialExpressionMultiply)
    contrast.set_editor_property('const_b', .48); wire(dot, contrast, 'A')
    ambient = node(unreal.MaterialExpressionAdd)
    ambient.set_editor_property('const_b', .52); wire(contrast, ambient, 'A')
    surface = node(unreal.MaterialExpressionMultiply); wire(base, surface, 'A'); wire(ambient, surface, 'B')
    final = node(unreal.MaterialExpressionMultiply); wire(color, final, 'A'); wire(surface, final, 'B')
    lib.connect_material_property(final, '', unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    lib.recompile_material(m)
    unreal.EditorAssetLibrary.save_loaded_asset(m)
    return m

mats = {
    'floor': material('M_DeckRidges', (.12,.17,.19), .16),
    'wall': material('M_WallRibs', (.025,.042,.055), .23),
    'metal': material('M_BrushedSteel', (.12,.19,.21), .08),
}
count = 0
for a in unreal.get_editor_subsystem(unreal.EditorActorSubsystem).get_all_level_actors():
    if not isinstance(a, unreal.StaticMeshActor): continue
    label = a.get_actor_label()
    key = None
    if label.startswith(('BayFloor','CellStep','LeftBoundary','RightBoundary')): key='floor'
    elif label.startswith(('BayBackdrop','Detail_EntryBackdrop')): key='wall'
    elif label.startswith(('FactoryColumn','Detail_UpperPipe','Detail_StorageCrate','Detail_Tank')): key='metal'
    if key:
        a.static_mesh_component.set_material(0, mats[key]); count += 1
assert unreal.EditorLoadingAndSavingUtils.save_map(world, '/Game/Maps/BetaIntegration')
unreal.log('FINAL_SURFACE_PASS_SAVED ' + str(count))
