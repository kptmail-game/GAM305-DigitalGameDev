import unreal
from pathlib import Path
root=Path(unreal.Paths.project_dir()); tools=unreal.AssetToolsHelpers.get_asset_tools()
meshes=[]
for folder in ['ChristianPipes','ChristianSwing']:
 for f in (root/'Saved/Week5Incoming'/folder).glob('*.fbx'):
  name='SM_'+''.join(c if c.isalnum() else '_' for c in f.stem)
  path='/Game/Team/Christian/'+name
  if not unreal.EditorAssetLibrary.does_asset_exist(path):
   t=unreal.AssetImportTask(); t.filename=str(f); t.destination_path='/Game/Team/Christian'; t.destination_name=name; t.automated=True; t.save=True
   o=unreal.FbxImportUI(); o.import_mesh=True; o.import_as_skeletal=False; o.import_materials=False; o.import_textures=False; o.mesh_type_to_import=unreal.FBXImportType.FBXIT_STATIC_MESH; o.static_mesh_import_data.combine_meshes=True; t.options=o
   tools.import_asset_tasks([t])
  mesh=unreal.load_asset(path); assert mesh
  mat=unreal.load_asset('/Game/Beta/M_MachineSteel'); mesh.set_material(0,mat); unreal.EditorAssetLibrary.save_loaded_asset(mesh)
  meshes.append((folder,mesh)); unreal.log('TEAM_MESH '+name+' '+str(mesh.get_bounding_box()))
world=unreal.EditorLoadingAndSavingUtils.load_map('/Game/Maps/BetaIntegration'); actors=unreal.get_editor_subsystem(unreal.EditorActorSubsystem)
for a in actors.get_all_level_actors():
 if a.get_actor_label().startswith('Christian_BetaPipe_'): actors.destroy_actor(a)
pipes=[m for f,m in meshes if f=='ChristianPipes']
for i,x in enumerate(range(1000,11500,1250)):
 m=pipes[i%len(pipes)]; b=m.get_bounding_box(); center=(b.min+b.max)*.5; scale=300/max(b.max.y-b.min.y,1)
 a=actors.spawn_actor_from_class(unreal.StaticMeshActor,unreal.Vector(x,-240,200)); a.set_actor_label('Christian_BetaPipe_'+str(i)); a.static_mesh_component.set_static_mesh(m); a.set_actor_scale3d(unreal.Vector(scale,scale,scale)); a.set_actor_rotation(unreal.Rotator(pitch=0,yaw=90,roll=0),False); a.set_actor_location(unreal.Vector(x,-240,280)-unreal.Vector(-center.y,center.x,center.z)*scale,False,False); a.set_actor_enable_collision(False)
swing=[m for f,m in meshes if f=='ChristianSwing'][0]
for a in actors.get_all_level_actors():
 if a.get_class().get_name()=='FactoryElement' and a.get_editor_property('kind')==unreal.FactoryElementKind.SWING_ARM:
  mesh=a.get_editor_property('mesh'); b=swing.get_bounding_box(); center=(b.min+b.max)*.5
  # Keep the visual inside the existing damage volume; preserve its tested motion and collision.
  extent=a.get_editor_property('trigger').get_unscaled_box_extent()*2
  dims=b.max-b.min; scale=min(extent.x/max(dims.x,1),extent.y/max(dims.y,1),extent.z/max(dims.z,1))
  mesh.set_static_mesh(swing); mesh.set_relative_scale3d(unreal.Vector(scale,scale,scale)); mesh.set_relative_location(-center*scale,False,False); mesh.set_material(0,unreal.load_asset('/Game/Beta/M_SafetyAmber'))
assert unreal.EditorLoadingAndSavingUtils.save_map(world,'/Game/Maps/BetaIntegration')
unreal.log('SATURDAY_BETA_ASSETS_SAVED')
