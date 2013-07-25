#include "hotpot/hp_platform.h"
#include "hotprotocol/hp_abstract_writer.h"

#include "syntactic_node.h"
#include "syntatic_node_writer.h"
#include <string.h>

void write_ST_UNIX_COMMENT_OR_NOT(HPAbstractWriter *self, const ST_UNIX_COMMENT_OR_NOT* data)
{ 
	write_struct_begin(self, "ST_UNIX_COMMENT_OR_NOT");

		write_field_begin(self, "empty", strlen("empty"));

		write_bool(self, data->empty);

		write_field_end(self, "empty", strlen("empty"));

		write_field_begin(self, "len", strlen("len"));

		write_uint32(self, data->len);

		write_field_end(self, "len", strlen("len"));

	write_field_begin(self, "text", strlen("text"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_COMMENT_LENGTH; ++i)
		{
			if( i == data->len )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_char(self, &data->text);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "text", strlen("text"));

	write_struct_end(self , "ST_UNIX_COMMENT_OR_NOT");
}

void write_UN_VALUE(HPAbstractWriter *self, const UN_VALUE* data , SN_VALUE_TYPE s)
{
	write_struct_begin(self, "UN_VALUE");
	switch(s)
	{

		case E_SNVT_INT64:
			write_int64(self, data->i64);
			break;
		case E_SNVT_HEX_INT64:
			write_int64(self, data->hex_i64);
			break;
		case E_SNVT_UINT64:
			write_uint64(self, data->ui64);
			break;
		case E_SNVT_HEX_UINT64:
			write_uint64(self, data->hex_ui64);
			break;
		case E_SNVT_BOOL:
			write_bool(self, data->b);
			break;
		case E_SNVT_IDENTIFIER:
			write_string(self, &data->identifier);
			break;
	}
	write_struct_end(self, "UN_VALUE");
}

void write_ST_VALUE(HPAbstractWriter *self, const ST_VALUE* data)
{ 
	write_struct_begin(self, "ST_VALUE");

		write_field_begin(self, "type", strlen("type"));

		//write_SN_VALUE_TYPE(self, &data->type);

		write_field_end(self, "type", strlen("type"));

		write_field_begin(self, "val", strlen("val"));

		write_UN_VALUE(self, &data->val, data->type);

		write_field_end(self, "val", strlen("val"));

	write_struct_end(self , "ST_VALUE");
}

void write_ST_TYPE(HPAbstractWriter *self, const ST_TYPE* data)
{ 
	write_struct_begin(self, "ST_TYPE");

		write_field_begin(self, "type", strlen("type"));

		//write_SN_TYPE(self, &data->type);

		write_field_end(self, "type", strlen("type"));

		write_field_begin(self, "st", strlen("st"));

		//if (type == E_SNT_SIMPLE) write_SN_SIMPLE_TYPE(self, &data->st);

		write_field_end(self, "st", strlen("st"));

		write_field_begin(self, "ct", strlen("ct"));

		//if (type == E_SNT_CONTAINER) write_SN_CONTAINER_TYPE(self, &data->ct);

		write_field_end(self, "ct", strlen("ct"));

	write_field_begin(self, "ot", strlen("ot"));

		//if (type == E_SNT_OBJECT) write_string(self, &data->ot);

	write_field_end(self, "ot", strlen("ot"));

	write_struct_end(self , "ST_TYPE");
}

void write_ST_Parameter(HPAbstractWriter *self, const ST_Parameter* data)
{ 
	write_struct_begin(self, "ST_Parameter");

		write_field_begin(self, "type", strlen("type"));

		write_ST_TYPE(self, &data->type);

		write_field_end(self, "type", strlen("type"));

	write_field_begin(self, "identifier", strlen("identifier"));

		write_string(self, &data->identifier);

	write_field_end(self, "identifier", strlen("identifier"));

	write_struct_end(self , "ST_Parameter");
}

void write_ST_Parameters(HPAbstractWriter *self, const ST_Parameters* data)
{ 
	write_struct_begin(self, "ST_Parameters");

		write_field_begin(self, "par_list_num", strlen("par_list_num"));

		write_uint32(self, data->par_list_num);

		write_field_end(self, "par_list_num", strlen("par_list_num"));

	write_field_begin(self, "par_list", strlen("par_list"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_PARAMETER_NUM; ++i)
		{
			if( i == data->par_list_num )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_ST_Parameter(self, &data->par_list);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "par_list", strlen("par_list"));

	write_struct_end(self , "ST_Parameters");
}

void write_ST_ARGUMENT(HPAbstractWriter *self, const ST_ARGUMENT* data)
{ 
	write_struct_begin(self, "ST_ARGUMENT");

	write_field_begin(self, "id", strlen("id"));

		write_string(self, &data->id);

	write_field_end(self, "id", strlen("id"));

	write_struct_end(self , "ST_ARGUMENT");
}

void write_ST_ARGUMENTS(HPAbstractWriter *self, const ST_ARGUMENTS* data)
{ 
	write_struct_begin(self, "ST_ARGUMENTS");

		write_field_begin(self, "arg_list_num", strlen("arg_list_num"));

		write_uint32(self, data->arg_list_num);

		write_field_end(self, "arg_list_num", strlen("arg_list_num"));

	write_field_begin(self, "arg_list", strlen("arg_list"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_ARGUMENT_NUM; ++i)
		{
			if( i == data->arg_list_num )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_ST_ARGUMENT(self, &data->arg_list);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "arg_list", strlen("arg_list"));

	write_struct_end(self , "ST_ARGUMENTS");
}

void write_ST_Expression(HPAbstractWriter *self, const ST_Expression* data)
{ 
	write_struct_begin(self, "ST_Expression");

		write_field_begin(self, "neg", strlen("neg"));

		write_bool(self, data->neg);

		write_field_end(self, "neg", strlen("neg"));

	write_field_begin(self, "op0", strlen("op0"));

		write_string(self, &data->op0);

	write_field_end(self, "op0", strlen("op0"));

	write_field_begin(self, "operator", strlen("operator"));

		write_string(self, &data->op0);

	write_field_end(self, "operator", strlen("operator"));

	write_field_begin(self, "op1", strlen("op1"));

		write_string(self, &data->op1);

	write_field_end(self, "op1", strlen("op1"));

	write_struct_end(self , "ST_Expression");
}

void write_ST_CONDITION(HPAbstractWriter *self, const ST_CONDITION* data)
{ 
	write_struct_begin(self, "ST_CONDITION");

		write_field_begin(self, "empty", strlen("empty"));

		write_bool(self, data->empty);

		write_field_end(self, "empty", strlen("empty"));

		write_field_begin(self, "exp", strlen("exp"));

		write_ST_Expression(self, &data->exp);

		write_field_end(self, "exp", strlen("exp"));

	write_struct_end(self , "ST_CONDITION");
}

void write_ST_FIELD(HPAbstractWriter *self, const ST_FIELD* data)
{ 
	write_struct_begin(self, "ST_FIELD");

		write_field_begin(self, "condition", strlen("condition"));

		write_ST_CONDITION(self, &data->condition);

		write_field_end(self, "condition", strlen("condition"));

		write_field_begin(self, "type", strlen("type"));

		write_ST_TYPE(self, &data->type);

		write_field_end(self, "type", strlen("type"));

		write_field_begin(self, "args", strlen("args"));

		write_ST_ARGUMENTS(self, &data->args);

		write_field_end(self, "args", strlen("args"));

	write_field_begin(self, "identifier", strlen("identifier"));

		write_string(self, &data->identifier);

	write_field_end(self, "identifier", strlen("identifier"));

		write_field_begin(self, "comment", strlen("comment"));

		write_ST_UNIX_COMMENT_OR_NOT(self, &data->comment);

		write_field_end(self, "comment", strlen("comment"));

	write_struct_end(self , "ST_FIELD");
}

void write_UN_TypeAnnotation(HPAbstractWriter *self, const UN_TypeAnnotation* data , TA_TYPE s)
{
	write_struct_begin(self, "UN_TypeAnnotation");
	switch(s)
	{

		case E_TA_SWITCH:
			write_string(self, &data->ta_switch);
			break;
		case E_TA_LOWER_BOUND:
			write_ST_VALUE(self, &data->ta_lower_bound);
			break;
		case E_TA_UPPER_BOUND:
			write_ST_VALUE(self, &data->ta_upper_bound);
			break;
	}
	write_struct_end(self, "UN_TypeAnnotation");
}

void write_ST_TypeAnnotation(HPAbstractWriter *self, const ST_TypeAnnotation* data)
{ 
	write_struct_begin(self, "ST_TypeAnnotation");

		write_field_begin(self, "type", strlen("type"));

		//write_TA_TYPE(self, &data->type);

		write_field_end(self, "type", strlen("type"));

		write_field_begin(self, "ta", strlen("ta"));

		//write_UN_TypeAnnotation(self, &data->ta, data->type, data->MAX_TA_LIST_NUM);

		write_field_end(self, "ta", strlen("ta"));

	write_struct_end(self , "ST_TypeAnnotation");
}

void write_ST_TypeAnnotations(HPAbstractWriter *self, const ST_TypeAnnotations* data)
{ 
	write_struct_begin(self, "ST_TypeAnnotations");

		write_field_begin(self, "ta_list_num", strlen("ta_list_num"));

		write_uint32(self, data->ta_list_num);

		write_field_end(self, "ta_list_num", strlen("ta_list_num"));

	write_field_begin(self, "ta_list", strlen("ta_list"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_TA_LIST_NUM; ++i)
		{
			if( i == data->ta_list_num )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_ST_TypeAnnotation(self, &data->ta_list);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "ta_list", strlen("ta_list"));

	write_struct_end(self , "ST_TypeAnnotations");
}

void write_ST_Import(HPAbstractWriter *self, const ST_Import* data)
{ 
	write_struct_begin(self, "ST_Import");

	write_field_begin(self, "package_name", strlen("package_name"));

		write_string(self, &data->package_name);

	write_field_end(self, "package_name", strlen("package_name"));

	write_struct_end(self , "ST_Import");
}

void write_ST_Const(HPAbstractWriter *self, const ST_Const* data)
{ 
	write_struct_begin(self, "ST_Const");

		write_field_begin(self, "type", strlen("type"));

		write_ST_TYPE(self, &data->type);

		write_field_end(self, "type", strlen("type"));

		write_field_begin(self, "val", strlen("val"));

		write_ST_VALUE(self, &data->val);

		write_field_end(self, "val", strlen("val"));

	write_struct_end(self , "ST_Const");
}

void write_ST_UNIX_COMMENT(HPAbstractWriter *self, const ST_UNIX_COMMENT* data)
{ 
	write_struct_begin(self, "ST_UNIX_COMMENT");

		write_field_begin(self, "len", strlen("len"));

		write_uint32(self, data->len);

		write_field_end(self, "len", strlen("len"));

	write_field_begin(self, "text", strlen("text"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_COMMENT_LENGTH; ++i)
		{
			if( i == data->len )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_char(self, &data->text);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "text", strlen("text"));

	write_struct_end(self , "ST_UNIX_COMMENT");
}

void write_ST_ENUM_DEF(HPAbstractWriter *self, const ST_ENUM_DEF* data)
{ 
	write_struct_begin(self, "ST_ENUM_DEF");

	write_field_begin(self, "identifier", strlen("identifier"));

		write_string(self, &data->identifier);

	write_field_end(self, "identifier", strlen("identifier"));

		write_field_begin(self, "val", strlen("val"));

		write_ST_VALUE(self, &data->val);

		write_field_end(self, "val", strlen("val"));

		write_field_begin(self, "comment", strlen("comment"));

		write_ST_UNIX_COMMENT_OR_NOT(self, &data->comment);

		write_field_end(self, "comment", strlen("comment"));

	write_struct_end(self , "ST_ENUM_DEF");
}

void write_ST_ENUM(HPAbstractWriter *self, const ST_ENUM* data)
{ 
	write_struct_begin(self, "ST_ENUM");

		write_field_begin(self, "enum_def_list_num", strlen("enum_def_list_num"));

		write_uint32(self, data->enum_def_list_num);

		write_field_end(self, "enum_def_list_num", strlen("enum_def_list_num"));

	write_field_begin(self, "enum_def_list", strlen("enum_def_list"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_ENUM_DEF_LIST_NUM; ++i)
		{
			if( i == data->enum_def_list_num )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_ST_ENUM_DEF(self, &data->enum_def_list);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "enum_def_list", strlen("enum_def_list"));

	write_struct_end(self , "ST_ENUM");
}

void write_ST_STRUCT(HPAbstractWriter *self, const ST_STRUCT* data)
{ 
	write_struct_begin(self, "ST_STRUCT");

		write_field_begin(self, "ta", strlen("ta"));

		write_ST_TypeAnnotations(self, &data->ta);

		write_field_end(self, "ta", strlen("ta"));

	write_field_begin(self, "name", strlen("name"));

		write_string(self, &data->name);

	write_field_end(self, "name", strlen("name"));

		write_field_begin(self, "parameters", strlen("parameters"));

		write_ST_Parameters(self, &data->parameters);

		write_field_end(self, "parameters", strlen("parameters"));

		write_field_begin(self, "field_list_num", strlen("field_list_num"));

		write_uint32(self, data->field_list_num);

		write_field_end(self, "field_list_num", strlen("field_list_num"));

	write_field_begin(self, "field_list", strlen("field_list"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_FIELD_LIST_NUM; ++i)
		{
			if( i == data->field_list_num )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_ST_FIELD(self, &data->field_list);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "field_list", strlen("field_list"));

	write_struct_end(self , "ST_STRUCT");
}

void write_ST_UNION(HPAbstractWriter *self, const ST_UNION* data)
{ 
	write_struct_begin(self, "ST_UNION");

		write_field_begin(self, "ta", strlen("ta"));

		write_ST_TypeAnnotations(self, &data->ta);

		write_field_end(self, "ta", strlen("ta"));

	write_field_begin(self, "name", strlen("name"));

		write_string(self, &data->name);

	write_field_end(self, "name", strlen("name"));

		write_field_begin(self, "parameters", strlen("parameters"));

		write_ST_Parameters(self, &data->parameters);

		write_field_end(self, "parameters", strlen("parameters"));

		write_field_begin(self, "field_list_num", strlen("field_list_num"));

		write_uint32(self, data->field_list_num);

		write_field_end(self, "field_list_num", strlen("field_list_num"));

	write_field_begin(self, "field_list", strlen("field_list"));
	write_vector_begin(self);
	{	
		hpuint32 i;
		for(i = 0; i < MAX_FIELD_LIST_NUM; ++i)
		{
			if( i == data->field_list_num )
			{
				break;
			}
			write_vector_item_begin(self, i);

			write_ST_FIELD(self, &data->field_list);

			write_vector_item_end(self, i);
		}
	}
	write_vector_end(self);
	write_field_end(self, "field_list", strlen("field_list"));

	write_struct_end(self , "ST_UNION");
}

