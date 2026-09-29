"""Small Beta-only material pass. Preserves meshes, collision, and teammate assets."""
import unreal
world=unreal.EditorLoadingAndSavingUtils.load_map('/Game/Maps/BetaIntegration')
tools=unreal.AssetToolsHelpers.get_asset_tools()
lib=unreal.MaterialEditingLibrary
unreal.EditorAssetLibrary.make_directory('/Game/Beta')
def material(name,rgb):
 m=unreal.load_asset('/Game/Beta/'+name)
 if m: return m
 m=tools.create_asset(name,'/Game/Beta',unreal.Material,unreal.MaterialFactoryNew())
 m.set_editor_property('shading_model',unreal.MaterialShadingModel.MSM_UNLIT)
 def node(cls): return lib.create_material_expression(m,cls)
 def wire(a,b,p): lib.connect_material_expressions(a,'',b,p)
 c=node(unreal.MaterialExpressionConstant3Vector); c.constant=unreal.LinearColor(*rgb,1)
 n=node(unreal.MaterialExpressionVertexNormalWS)
 d=node(unreal.MaterialExpressionConstant3Vector); d.constant=unreal.LinearColor(-.45,.35,.82,1)
 dot=node(unreal.MaterialExpressionDotProduct); wire(n,dot,'A'); wire(d,dot,'B')
 shade=node(unreal.MaterialExpressionMultiply); shade.set_editor_property('const_b',.48); wire(dot,shade,'A')
 amb=node(unreal.MaterialExpressionAdd); amb.set_editor_property('const_b',.52); wire(shade,amb,'A')
 final=node(unreal.MaterialExpressionMultiply); wire(c,final,'A'); wire(amb,final,'B')
 lib.connect_material_property(final,'',unreal.MaterialProperty.MP_EMISSIVE_COLOR)
 lib.recompile_material(m); unreal.EditorAssetLibrary.save_loaded_asset(m); return m
mats={
 'floor':material('M_FloorSteelShaded',(.15,.19,.21)),
 'wall':material('M_WallSteelShaded',(.035,.05,.065)),
 'metal':material('M_MachineSteel',(.16,.20,.22)),
 'trim':material('M_DarkTrim',(.045,.065,.075)),
 'warm':material('M_WarmLamp',(1,.62,.22)),
 'amber':material('M_SafetyAmber',(.8,.39,.045)),
}
count=0
for a in unreal.get_editor_subsystem(unreal.EditorActorSubsystem).get_all_level_actors():
 if not isinstance(a,unreal.StaticMeshActor): continue
 label=a.get_actor_label(); key=None
 if label.startswith(('BayFloor','CellStep','LeftBoundary','RightBoundary')): key='floor'
 elif label.startswith(('BayBackdrop','Detail_EntryBackdrop')): key='wall'
 elif label.startswith(('FactoryColumn','Detail_UpperPipe','Detail_StorageCrate','Detail_Tank')): key='metal'
 elif label.startswith(('Detail_LampStrip','Detail_ExitHeader')): key='warm'
 elif label.startswith(('Detail_CrateBand','Detail_ObjectiveStripe','Detail_CellSocket')): key='amber'
 elif label.startswith(('Detail_Floor','Detail_LampHousing','Detail_ExitFrame')): key='trim'
 if key: a.static_mesh_component.set_material(0,mats[key]); count+=1
assert unreal.EditorLoadingAndSavingUtils.save_map(world,'/Game/Maps/BetaIntegration')
unreal.log('BETA_VISUAL_PASS_SAVED '+str(count))



