"""Run once with UnrealEditor-Cmd -run=pythonscript -script=<this file>."""
import unreal

world = unreal.EditorLoadingAndSavingUtils.new_blank_map(False)
actors = unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
cube = unreal.load_asset('/Engine/BasicShapes/Cube')
tools = unreal.AssetToolsHelpers.get_asset_tools()
unreal.EditorAssetLibrary.make_directory('/Game/Prototype')
def color_material(name, color):
    asset = unreal.load_asset('/Game/Prototype/' + name)
    if not asset:
        asset = tools.create_asset(name, '/Game/Prototype', unreal.Material, unreal.MaterialFactoryNew())
        asset.set_editor_property('shading_model', unreal.MaterialShadingModel.MSM_UNLIT)
        value = unreal.MaterialEditingLibrary.create_material_expression(asset, unreal.MaterialExpressionConstant3Vector)
        value.set_editor_property('constant', unreal.LinearColor(*color, 1))
        unreal.MaterialEditingLibrary.connect_material_property(value, '', unreal.MaterialProperty.MP_EMISSIVE_COLOR)
        unreal.MaterialEditingLibrary.recompile_material(asset)
        unreal.EditorAssetLibrary.save_loaded_asset(asset)
    return asset
material = color_material('M_Platform', (.12,.4,.48))
backdrop = color_material('M_Backdrop', (.025,.04,.075))
color_material('M_Player', (1,.3,.035))

def block(name, location, scale):
    actor = actors.spawn_actor_from_class(unreal.StaticMeshActor, unreal.Vector(*location))
    actor.set_actor_label(name)
    mesh = actor.static_mesh_component
    mesh.set_static_mesh(cube)
    mesh.set_material(0, material)
    actor.set_actor_scale3d(unreal.Vector(*scale))
    return actor

# Broad platforms leave room to learn movement before two recoverable gaps.
block('StartFloor', (350, 0, -50), (12, 5, 1))
block('MiddleFloor', (1700, 0, -50), (10, 5, 1))
block('FinishFloor', (2850, 0, -50), (10, 5, 1))
block('StepOne', (400, 0, 30), (1.5, 4, .6))
block('StepTwo', (650, 0, 65), (1.5, 4, 1.3))
block('RaisedPlatform', (1575, 0, 70), (2.5, 4, 1.4))
block('LeftBoundary', (-275, 0, 200), (.5, 5, 5))
block('RightBoundary', (3375, 0, 200), (.5, 5, 5))
back = block('Backdrop', (1550, -300, 300), (80, .3, 30))
back.static_mesh_component.set_material(0, backdrop)
actors.spawn_actor_from_class(unreal.PlayerStart, unreal.Vector(0, 0, 95))
light = actors.spawn_actor_from_class(unreal.DirectionalLight, unreal.Vector(0,-300,700), unreal.Rotator(-35,-90,0))
light.light_component.set_mobility(unreal.ComponentMobility.MOVABLE)
light.light_component.set_editor_property('intensity', 4.0)
sky = actors.spawn_actor_from_class(unreal.SkyLight, unreal.Vector(0,0,500))
sky.light_component.set_mobility(unreal.ComponentMobility.MOVABLE)
sky.light_component.set_editor_property('intensity', 1.0)
unreal.EditorAssetLibrary.make_directory('/Game/Maps')
assert unreal.EditorLoadingAndSavingUtils.save_map(world, '/Game/Maps/Prototype')
unreal.log('PROTOTYPE_MAP_CREATED')

