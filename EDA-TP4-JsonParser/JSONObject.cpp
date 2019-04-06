#include "JSONObject.h"
#include <iostream>;
#define INITIALSIZE 100

JSONObject::JSONObject(void){
}

JSONObject::JSONObject(string& s)
{
	if (!ErrorCheck(s)) { //el string que parseamos esta bien formado
		cantFields = 0;
		string tosave; //realocar vector de fields?
		int sum=0; 
		enum states {INITIAL, NEWFIELD, FIELDNAME, FIELDCONTENT, NEWCONTENT, DONE};
		string::iterator iter;
		iter = s.begin();
		states state = INITIAL;
			while(iter<s.end()){
				switch (state) {
				case INITIAL: { if (*iter == '"') {
					state = NEWFIELD;
				}
				}
							  break;
				case NEWFIELD: {
					cantFields++;
					tosave = "";
					tosave.push_back(*iter);
					state = FIELDNAME;
				}
							   break;
				case FIELDNAME: {if (*iter != '"') {
					    tosave.push_back(*iter);
				        }
								else
				        {
					    fields[cantFields].setFieldName(tosave);
				     	state = NEWCONTENT;
				        }
						}
								break;
				case NEWCONTENT: { if (*iter == '{') {
					sum++;
					state = FIELDCONTENT;
				}
				}
								 break;
				case FIELDCONTENT: {
					if (*iter == '{') {
						sum++;
					}
					if (*iter == '}') {
						sum--;
					}
					if (sum != 0) {
						tosave.push_back(*iter);
					}
					else if (sum == 0) {
						sum = 0;
						fields[cantFields].setContent(tosave);
						state = DONE;
					}

				}
								   break;
				case DONE: {if (*iter == '"') {
					state = NEWFIELD;
				}

				}
						   break;
				}
				iter++;
				}
			}

	}
	


JSONObject::JSONObject(const char * s)
{
	string to_app;
	to_app.append(s);
	JSONObject(s);

}

const char * 
JSONObject::getFieldType(const char * f)
{
	bool found = false;
	const char* type = "invalid";

	for (int i = 0; i < fieldCount && !found; i++)
	{
		found = fields[i].getFieldName() == f;

		if (found)
		{
			i--;
			if (fields[i].getFieldType() == string("object"))
				type = "object";
			else if (fields[i].getFieldType() == string("array"))
				type = "array";
			else if (fields[i].getFieldType() == string("string"))
				type = "string";
			else if (fields[i].getFieldType() == string("number"))
				type = "number";
			else if (fields[i].getFieldType() == string("bool"))
				type = "bool";
		}
	}

	return type;
}

void*
JSONObject::copyField(const char* f)	//le falta todavia, solo copie lo que hicimos en clase
{
	bool found = false;
	for (int i = 0; i < fieldCount && !found; i++)
	{
		found = fields[i].getFieldName() == f;

		if (found)
		{
			i--;
			if (fields[i].getFieldType() == string("object"))
				JSONObject* newJSON = new JSONObject(fields[i].getContent());
			else if (fields[i].getFieldType() == string("number"))
				double* newJSON = new double(stod(fields[i].getContent()));
		}
	}
}
