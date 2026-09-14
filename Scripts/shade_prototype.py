"""Add directional face shading to existing prototype materials without changing the map."""
import unreal

def shade(name, color):
    material = unreal.load_asset('/Game/Prototype/' + name)
    if not material:
        raise RuntimeError('Missing prototype material: ' + name)
    edit = unreal.MaterialEditingLibrary
    edit.delete_all_material_expressions(material)
    material.set_editor_property('shading_model', unreal.MaterialShadingModel.MSM_UNLIT)

    # World-space face normals give the block tops and sides distinct values,
    # with ambient fill keeping every face readable without baked lighting.
    normal = edit.create_material_expression(material, unreal.MaterialExpressionVertexNormalWS)
    light = edit.create_material_expression(material, unreal.MaterialExpressionConstant3Vector)
    light.set_editor_property('constant', unreal.LinearColor(-0.6, 0.3, 0.7416, 1))
    dot = edit.create_material_expression(material, unreal.MaterialExpressionDotProduct)
    edit.connect_material_expressions(normal, '', dot, 'A')
    edit.connect_material_expressions(light, '', dot, 'B')
    half = edit.create_material_expression(material, unreal.MaterialExpressionMultiply)
    half.set_editor_property('const_b', 0.5)
    edit.connect_material_expressions(dot, '', half, 'A')
    fill = edit.create_material_expression(material, unreal.MaterialExpressionAdd)
    fill.set_editor_property('const_b', 0.5)
    edit.connect_material_expressions(half, '', fill, 'A')
    base = edit.create_material_expression(material, unreal.MaterialExpressionConstant3Vector)
    base.set_editor_property('constant', unreal.LinearColor(*color, 1))
    result = edit.create_material_expression(material, unreal.MaterialExpressionMultiply)
    edit.connect_material_expressions(base, '', result, 'A')
    edit.connect_material_expressions(fill, '', result, 'B')
    edit.connect_material_property(result, '', unreal.MaterialProperty.MP_EMISSIVE_COLOR)
    edit.layout_material_expressions(material)
    edit.recompile_material(material)
    unreal.EditorAssetLibrary.save_loaded_asset(material)

shade('M_Platform', (0.12, 0.4, 0.48))
shade('M_Player', (1, 0.3, 0.035))
unreal.log('PROTOTYPE_SHADING_UPDATED')
