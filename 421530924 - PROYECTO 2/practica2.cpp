//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
//shader color
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//rojo shader
static const char* rojoFShader = "shaders/rojoFShader.frag";
static const char* rojoVShader = "shaders/rojoVShader.vert";
//verde shader
static const char* verdeFShader = "shaders/verdeFShader.frag";
static const char* verdeVShader = "shaders/verdeVShader.vert";
//azul shader
static const char* azulFShader = "shaders/azulFShader.frag";
static const char* azulVShader = "shaders/azulVShader.vert";
//cafe shader
static const char* cafeFShader = "shaders/cafeFShader.frag";
static const char* cafeVShader = "shaders/cafeVShader.vert";
//verde Oscuro shader
static const char* verdeOFShader = "shaders/verdeOFShader.frag";
static const char* verdeOVShader = "shaders/verdeOVShader.vert";


float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B

		//LETRA L
			-0.8f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.8f,	1.8f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.6f,	1.8f,		0.5f,			0.0f,	0.0f,	1.0f,

			-0.8f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.6f,	1.8f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.6f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

			-0.6f,	1.2f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.6f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.4f,	1.2f,		0.5f,			0.0f,	0.0f,	1.0f,

			-0.6f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.4f,	1.2f,		0.5f,			0.0f,	0.0f,	1.0f,
			-0.4f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

			//FIN DE LA LETRA L

			//LETRA E

			-0.1f,	1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.0f,	1.8f,		0.5f,			0.0f,	1.0f,	0.0f,
			-0.1f,	1.8f,		0.5f,			0.0f,	1.0f,	0.0f,

			 0.0f,	1.8f,		0.5f,			0.0f,	1.0f,	0.0f,
			-0.1f,	1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.0f,	1.0f,		0.5f,			0.0f,	1.0f,	0.0f,

			 0.0f,	1.6f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.2f,	1.8f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.0f,	1.8f,		0.5f,			0.0f,	1.0f,	0.0f,

			 0.0f,	1.6f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.2f,	1.8f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.2f,	1.6f,		0.5f,			0.0f,	1.0f,	0.0f,

			 0.0f,	1.45f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.0f,	1.25f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.2f,	1.45f,		0.5f,			0.0f,	1.0f,	0.0f,

			 0.2f,	1.45f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.0f,	1.25f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.2f,	1.25f,		0.5f,			0.0f,	1.0f,	0.0f,

			 0.0f,	1.13f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.0f,	1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.2f,	1.13f,		0.5f,			0.0f,	1.0f,	0.0f,

			 0.2f,	1.13f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.0f,	1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
			 0.2f,	1.0f,		0.5f,			0.0f,	1.0f,	0.0f,

			 //FIN DE LA LETRA E 


					 //cuadro negro
			 0.69f,	1.55f,		0.5f,			0.0f,	0.0f,	0.0f,
			 0.8f,	1.7f,		0.5f,			0.0f,	0.0f,	0.0f,
			 0.68f,	1.7f,		0.5f,			0.0f,	0.0f,	0.0f,

			 0.69f,	1.55f,		0.5f,			0.0f,	0.0f,	0.0f,
			 0.8f,	1.7f,		0.5f,			0.0f,	0.0f,	0.0f,
			 0.8f,	1.55f,		0.5f,			0.0f,	0.0f,	0.0f,



			 //LETRA R

			 0.5f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.6f,	1.8f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.5f,	1.8f,		0.5f,			1.0f,	0.0f,	0.0f,

			 0.5f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.6f,	1.8f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.6f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

			 0.6f,	1.4f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.9f,	1.8f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.6f,	1.8f,		0.5f,			1.0f,	0.0f,	0.0f,

			 0.6f,	1.4f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.9f,	1.8f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.9f,	1.4f,		0.5f,			1.0f,	0.0f,	0.0f,

			 0.8f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.64f,	1.45f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.56f,	1.36f,		0.5f,			1.0f,	0.0f,	0.0f,

			 0.8f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.64f,	1.45f,		0.5f,			1.0f,	0.0f,	0.0f,
			 0.9f,	1.11f,		0.5f,			1.0f,	0.0f,	0.0f,
			 


			
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,360);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {

		//X			Y			Z			R		G		B
		//techo de la casa color azul
		-0.4f,	0.1f,		0.5f,			0.0f,	0.0f,	0.0f,
		0.3f,	0.1f,		0.5f,			0.0f,	0.0f,	0.0f,
		-0.04f,	0.4f,		0.5f,			0.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


}


void CreateShaders()
{
	Shader* shader1 = new Shader(); 
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1); //shader 0

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);//shader 1

	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(rojoVShader, rojoFShader);
	shaderList.push_back(*shader3); //shaderList[2] rojo

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(verdeVShader, verdeFShader);
	shaderList.push_back(*shader4); //shaderList[3]verde

	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(azulVShader, azulFShader);
	shaderList.push_back(*shader5); //shaderList[4]azul

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(cafeVShader, cafeFShader);
	shaderList.push_back(*shader6); //shaderList[5]cafe

	Shader* shader7 = new Shader();
	shader7->CreateFromFiles(verdeOVShader, verdeOFShader);
	shaderList.push_back(*shader7); //shaderList[6]verde oscuro 
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{

		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana 
		glClearColor(0.0f,0.0f,0.0f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		
		/*//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();
		//1 es el triaungulo color rojo
		//0 es el de crear las letras
		*/
		//Para el cubo y la pirámide se usa el primer set de shaders con índice 0 en ShaderList
		//ShaderList es para agarrar los shaderList . frag y .Vert
		shaderList[0].useShader(); 
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;


		//LETRAS LER
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -2.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();


		//cuerpo de la casa
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -2.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
												
		//parte superior de la casa 
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.20f, -1.8f));
		model = glm::scale(model, glm::vec3(1.1f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//izquierda arbol 1 //hojas
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.3f, -1.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		
		//izquierda arbol 1 //tronco  
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.6f, -1.85f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// derecha arbol 2 //hojas
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.8f, -0.3f, -1.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//derecha arbol 2 //tronco
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.8f, -0.6f, -1.85f));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//puerta de la casa // puerta vede 
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.70f, -1.0f));
		model = glm::scale(model, glm::vec3(0.19f, 0.21f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//ventana 1 //izquierda 
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.26f, -0.2f, -1.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//ventana 2 //derecha
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.26f, -0.2f, -1.0f));
		model = glm::scale(model, glm::vec3(0.17f, 0.17f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;

}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/