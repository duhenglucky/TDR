#include "generate/generator_types_h.h"
#include "generator.h"
#include "version.h"
#include "symbols.h"

#include <stdio.h>
#include <string.h>


static error_code_t on_document_begin(generator_t *super, const YYLTYPE *yylloc, const char *file_name)
{
	TLIBC_UNUSED(yylloc);

	generator_open(super, file_name, GENERATOR_TYPES_H_SUFFIX);

	generator_printline(super, 0, "/**");
    generator_printline(super, 0, " * Autogenerated by %s Compiler (%s)", PROJECT_NAME, VERSION);
    generator_printline(super, 0, " *");
    generator_printline(super, 0, " * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING");
    generator_printline(super, 0, " *  @generated");
    generator_printline(super, 0, " */");
	generator_printline(super, 0, "");



	generator_printline(super, 0, "#ifndef _H_%s", super->document_name);
	generator_printline(super, 0, "#define _H_%s", super->document_name);
	generator_printline(super, 0, "");

	generator_printline(super, 0, "");
	generator_printline(super, 0, "#ifdef  __cplusplus");
	generator_printline(super, 0, "extern \"C\" {");
	generator_printline(super, 0, "#endif");
	generator_printline(super, 0, "");

	generator_printline(super, 0, "#include <stdint.h>");
	
	generator_printline(super, 0, "");
	generator_printline(super, 0, "");
	return E_TD_NOERROR;
}

static error_code_t on_document_end(generator_t *super, const YYLTYPE *yylloc, const char *file_name)
{
	TLIBC_UNUSED(yylloc);
	TLIBC_UNUSED(file_name);

	generator_printline(super, 0, "");
	generator_printline(super, 0, "#ifdef  __cplusplus");
	generator_printline(super, 0, "}");
	generator_printline(super, 0, "#endif");
	generator_printline(super, 0, "");

	generator_printline(super, 0, "");
	generator_printline(super, 0, "#endif //_H_%s", super->document_name);
	generator_printline(super, 0, "");

	generator_close(super);
	return E_TD_NOERROR;
}

static error_code_t _on_import(generator_types_h_t *self, const syn_import_t *de_import)
{
	char name[MAX_PACKAGE_NAME_LENGTH];	
	strncpy_notdir(name, de_import->package_name, MAX_PACKAGE_NAME_LENGTH - 1);
	generator_replace_extension(name, MAX_PACKAGE_NAME_LENGTH, GENERATOR_TYPES_H_SUFFIX);
	generator_printline(&self->super, 0, "#include \"%s\"", name);

	return E_TD_NOERROR;
}




static error_code_t _on_const(generator_types_h_t *self, const syn_const_t *de_const)
{
	generator_print(&self->super, 0, "#define %s ", de_const->identifier);
	generator_print_value(&self->super, &de_const->val);
	generator_printline(&self->super, 0, "");
	generator_printline(&self->super, 0, "");
	return E_TD_NOERROR;
}

static error_code_t _on_enum(generator_types_h_t *self, const syn_enum_t *de_enum)
{
	uint32_t i;	
	generator_printline(&self->super, 0, "typedef enum %s", de_enum->name);
	generator_printline(&self->super, 0, "{");
	for(i = 0;i < de_enum->enum_def_list_num; ++i)
	{
		generator_print(&self->super, 0, "\t%s = ", de_enum->enum_def_list[i].identifier);
		generator_print_value(&self->super, &de_enum->enum_def_list[i].val);
		generator_print(&self->super, 0, ",");
		if(de_enum->enum_def_list[i].comment.text[0])
		{
			generator_printline(&self->super, 0, "//%s", de_enum->enum_def_list[i].comment.text);
		}
		else
		{
			generator_printline(&self->super, 0, "");
		}		
	}
	generator_printline(&self->super, 0, "}%s_t;", de_enum->name);
	generator_printline(&self->super, 0, "");

	return E_TD_NOERROR;
}

static error_code_t _on_field_list(generator_types_h_t *self, const syn_field_list_t *field_list)
{
	uint32_t i;
	for(i = 0; i < field_list->field_list_num; ++i)
	{
		if(field_list->field_list[i].type.type == E_SNT_CONTAINER)
		{
			//为vector对象自动生成一个计数器对象, 所以一个vector类型的对象需要占用两个符号。
			if(field_list->field_list[i].type.ct.ct == E_CT_VECTOR)
			{
				generator_print(&self->super, 1, "");
				generator_print_ctype(&self->super, &g_vec_num_type);
				
				generator_printline(&self->super, 0, " "VEC_NUM_TYPE_STYLE";", field_list->field_list[i].identifier);
				
				
				generator_print(&self->super, 1, "");
				generator_print_ctype(&self->super, &field_list->field_list[i].type.ct.vector_type);
				
				generator_print(&self->super, 0, " %s", field_list->field_list[i].identifier);				
				generator_print(&self->super, 0, "[%s]", field_list->field_list[i].type.ct.vector_length);
				if(field_list->field_list[i].type.ct.vector_type.st == E_ST_STRING)
				{
					generator_print(&self->super, 0, "[%s]", field_list->field_list[i].type.ct.vector_type.string_length);
				}				
			}
		}
		else
		{
			generator_print(&self->super, 1, "");
			generator_print_ctype(&self->super, &field_list->field_list[i].type.st);
			generator_print(&self->super, 0, " %s", field_list->field_list[i].identifier);

			if(field_list->field_list[i].type.st.st == E_ST_STRING)
			{
				generator_print(&self->super, 0, "[%s]", field_list->field_list[i].type.st.string_length);
			}
			generator_print(&self->super, 0, "");
		}

		generator_print(&self->super, 0, ";");
		if(field_list->field_list[i].comment.text[0])
		{
			generator_print(&self->super, 0, "//%s", field_list->field_list[i].comment.text);
		}
		generator_printline(&self->super, 0, "");
	}

	return E_TD_NOERROR;
}

static error_code_t _on_struct(generator_types_h_t *self, const syn_struct_t *de_struct)
{	
	generator_printline(&self->super, 0, "typedef struct %s", de_struct->name);
	generator_printline(&self->super, 0, "{");
	_on_field_list(self, &de_struct->field_list);
	generator_printline(&self->super, 0, "}%s_t;", de_struct->name);
	generator_printline(&self->super, 0, "");

	return E_TD_NOERROR;
}


static error_code_t _on_union_field_list(generator_types_h_t *self, const syn_union_field_list_t *union_field_list)
{
	uint32_t i;
	for(i = 0; i < union_field_list->union_field_list_num; ++i)
	{
		generator_print(&self->super, 1, "");
		generator_print_ctype(&self->super, &union_field_list->union_field_list[i].simple_type);
		generator_print(&self->super, 0, " %s", union_field_list->union_field_list[i].name);

		if(union_field_list->union_field_list[i].simple_type.st == E_ST_STRING)
		{
			generator_print(&self->super, 0, "[%s]", union_field_list->union_field_list[i].name, union_field_list->union_field_list[i].simple_type.string_length);
		}
		
		generator_print(&self->super, 0, ";");
		if(union_field_list->union_field_list[i].comment.text[0])
		{
			generator_print(&self->super, 0, "//%s", union_field_list->union_field_list[i].comment.text);
		}
		generator_printline(&self->super, 0, "");
	}

	return E_TD_NOERROR;
}

static error_code_t _on_union(generator_types_h_t *self, const syn_union_t *de_union)
{
	generator_printline(&self->super, 0, "typedef union %s", de_union->name);
	generator_printline(&self->super, 0, "{");
	_on_union_field_list(self, &de_union->union_field_list);
	generator_printline(&self->super, 0, "}%s_t;", de_union->name);
	generator_printline(&self->super, 0, "");

	return E_TD_NOERROR;
}

static error_code_t _on_typedef(generator_types_h_t *self, const syn_typedef_t *de_typedef)
{
	generator_print(&self->super, 0, "typedef ");
	generator_print_ctype(&self->super, &de_typedef->type);
	generator_print(&self->super, 0, " %s", de_typedef->name);
	if(de_typedef->type.st == E_ST_STRING)
	{
		generator_print(&self->super, 0, "[%s]", de_typedef->type.string_length);
	}
	generator_print(&self->super, 0, ";");
	generator_printline(&self->super, 0, "");
	return E_TD_NOERROR;
}

static error_code_t _on_comment(generator_types_h_t *self, const syn_unix_comment_t *de_unix_comment)
{
	if(de_unix_comment->text[0])
	{
		generator_printline(&self->super, 0, "//%s", de_unix_comment->text);
	}
	return E_TD_NOERROR;
}

static error_code_t on_definition(generator_t *super, const YYLTYPE *yylloc, const syn_definition_t *definition)
{
	generator_types_h_t *self = TLIBC_CONTAINER_OF(super, generator_types_h_t, super);
	TLIBC_UNUSED(yylloc);
	switch(definition->type)
	{
		case E_DT_IMPORT:
			return _on_import(self, &definition->definition.de_import);				
		case E_DT_CONST:
			return _on_const(self, &definition->definition.de_const);
		case E_DT_ENUM:
			return _on_enum(self, &definition->definition.de_enum);
		case E_DT_STRUCT:
			return _on_struct(self, &definition->definition.de_struct);
		case E_DT_UNION:
			return _on_union(self, &definition->definition.de_union);
		case E_DT_TYPEDEF:
			return _on_typedef(self, &definition->definition.de_typedef);
		case E_DT_UNIX_COMMENT:
			return _on_comment(self, &definition->definition.de_unix_comment);
		default:
			return E_TD_ERROR;
	}
}

void generator_types_h_init(generator_types_h_t *self, const symbols_t *symbols)
{
	generator_init(&self->super, symbols);

	self->super.on_document_begin = on_document_begin;
	self->super.on_document_end = on_document_end;
	self->super.on_definition = on_definition;
}
