import unreal
from pathlib import Path
root=Path(unreal.Paths.project_dir())
src=root/'Saved/Week5Incoming/ChristianWallPanel'
tools=unreal.AssetToolsHelpers.get_asset_tools()
tasks=[]
for filename,name in [('wall panelwithline.fbx','SM_ChristianWallPanel'),('wall panel texture1.png','T_ChristianWallPanel')]:
 t=unreal.AssetImportTask(); t.filename=str(src/filename); t.destination_path='/Game/Team/Christian'; t.destination_name=name; t.automated=True; t.save=True; t.replace_existing=False
 if filename.endswith('.fbx'):
  o=unreal.FbxImportUI(); o.import_mesh=True; o.import_as_skeletal=False; o.import_materials=False; o.import_textures=False; o.mesh_type_to_import=unreal.FBXImportType.FBXIT_STATIC_MESH
  t.options=o
 tasks.append(t)
tools.import_asset_tasks([t for t in tasks if not unreal.EditorAssetLibrary.does_asset_exist(t.destination_path+'/'+t.destination_name)])
for t in tasks: unreal.log('WALL_IMPORT '+str(t.imported_object_paths))
mesh=unreal.load_asset('/Game/Team/Christian/SM_ChristianWallPanel')
assert mesh, 'Mesh import failed'
unreal.log('WALL_BOUNDS '+str(mesh.get_bounding_box()))
tex=unreal.load_asset('/Game/Team/Christian/T_ChristianWallPanel')
assert tex, 'Texture import failed'
mat=unreal.load_asset('/Game/Team/Christian/M_ChristianWallPanel') or tools.create_asset('M_ChristianWallPanel','/Game/Team/Christian',unreal.Material,unreal.MaterialFactoryNew())
mat.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_UNLIT)
expr=unreal.MaterialEditingLibrary.create_material_expression(mat,unreal.MaterialExpressionTextureSample)
expr.texture=tex
unreal.MaterialEditingLibrary.connect_material_property(expr,'RGB',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
unreal.MaterialEditingLibrary.recompile_material(mat)
mesh.set_material(0,mat)
unreal.EditorAssetLibrary.save_loaded_asset(mat); unreal.EditorAssetLibrary.save_loaded_asset(mesh)
world=unreal.EditorLoadingAndSavingUtils.load_map('/Game/Maps/AlphaIntegration')
actors=unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
for i,x in enumerate([700,1700,3700,4700,6700,7700,9700,10700]):
 a=actors.spawn_actor_from_class(unreal.StaticMeshActor,unreal.Vector(x,-285,40),unreal.Rotator(pitch=0,yaw=90,roll=0))
 a.set_actor_label('Christian_WallPanel_'+str(i+1)); a.static_mesh_component.set_static_mesh(mesh); a.set_actor_enable_collision(False)
assert unreal.EditorLoadingAndSavingUtils.save_map(world,'/Game/Maps/BetaIntegration')
unreal.log('WALL_BETA_SAVED')

