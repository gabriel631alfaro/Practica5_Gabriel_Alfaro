/*
Practica5. Modelado Jerarquico         José Gabriel Alfaro Fragoso
Fecha de entrega: 07/03/2025                   317019450
*/


#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f;
float codo = 0.0f;
float muneca = 0.0f;
float dedo11 = 0.0f;
float dedo12 = 0.0f;
float dedo13 = 0.0f;

float dedo21 = 0.0f;
float dedo22 = 0.0f;
float dedo23 = 0.0f;

float dedo31 = 0.0f;
float dedo32 = 0.0f;
float dedo33 = 0.0f;

float dedo41 = 0.0f;
float dedo42 = 0.0f;
float dedo43 = 0.0f;

float pulgar1 = 0.0f;
float pulgar2 = 0.0f;

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 5.Modelado jerarquico. Gabriel Alfaro", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	// use with Orthographic Projection




	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		0.5f,  0.5f, 0.5f,
		-0.5f,  0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		-0.5f, -0.5f,-0.5f,
		 0.5f, -0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		 0.5f,  0.5f,-0.5f,
		-0.5f,  0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		0.5f,  0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);



	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color = glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{

		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp3 = glm::mat4(1.0f); //Temp


		//View set up 
		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));


		glBindVertexArray(VAO);

		//Model Bicep 
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f)); //pivote trasladado 
		model = glm::scale(model, glm::vec3(1.2f, 0.5f, 0.5f));
		color = glm::vec3(0.545f, 0.961f, 0.808f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Model antebrazo 
		model = glm::translate(modelTemp, glm::vec3(0.75f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 0.5f));
		color = glm::vec3(0.937f, 0.549f, 0.961f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//Model Palma
		model = glm::translate(modelTemp, glm::vec3(0.41f, 0.0f, 0.0f));//distancia del antebrazo y la muñeca modificar disancia de dedos
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.215f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.5f, 0.5f));
		color = glm::vec3(1.0, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		// Model dedo1 A (Primera falange)
		model = glm::translate(modelTemp, glm::vec3(-0.13f, 0.175f, 0.1875f));
		model = glm::rotate(model, glm::radians(dedo11), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.08f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //D

		// Model dedo1 B (Segunda falange)
		model = glm::translate(modelTemp, glm::vec3(-0.131f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo12), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f)); // ACTUALIZAMOS modelTemp para que dedo13 dependa de dedo12
		model = glm::scale(model, glm::vec3(0.225f, 0.10f, 0.08f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); //E

		// Model dedo1 C (Tercera falange) 
		model = glm::translate(modelTemp, glm::vec3(0.225f, 0.0f, 0.0f)); // parte de la segunda falange
		model = glm::rotate(model, glm::radians(dedo13), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(0.0f, 0.f, 0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(0.23f, 0.10f, 0.08f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange


		//Model dedo2 A
		model = glm::translate(modelTemp, glm::vec3(-0.7f, 0.0f, -0.12));
		model = glm::rotate(model, glm::radians(dedo21), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.08f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D


		//Model dedo2 B
		model = glm::translate(modelTemp, glm::vec3(-0.138f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo22), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.225f, 0.10f, 0.08f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		// Model dedo2 C (Tercera falange)
		model = glm::translate(modelTemp, glm::vec3(0.225f, 0.0f, 0.0f)); // Traslada desde la punta de la segunda falange
		model = glm::rotate(model, glm::radians(dedo23), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(0.27f, 0.0f, -0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(0.23f, 0.10f, 0.08f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange

		//Model dedo3 A
		model = glm::translate(modelTemp, glm::vec3(-0.42f, 0.0f, -0.12));
		model = glm::rotate(model, glm::radians(dedo31), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.08f));
		color = glm::vec3(1.0, 1.0f, 0.45f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D


		//Model dedo3 B
		model = glm::translate(modelTemp, glm::vec3(-0.138f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo32), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.225f, 0.10f, 0.08f));
		color = glm::vec3(1.0, 0.45f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		// Model dedo3 C (Tercera falange)
		model = glm::translate(modelTemp, glm::vec3(0.225f, 0.0f, 0.0f)); // Traslada desde la punta de la segunda falange
		model = glm::rotate(model, glm::radians(dedo33), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(0.26f, 0.0f, -0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(0.23f, 0.10f, 0.08f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange


		//Model dedo4 A
		model = glm::translate(modelTemp, glm::vec3(-0.42f, 0.0f, -0.14));
		model = glm::rotate(model, glm::radians(dedo41), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.08f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D


		//Model dedo4 B
		model = glm::translate(modelTemp, glm::vec3(-0.138f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo42), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.4f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.225f, 0.10f, 0.08f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E

		// Model dedo4 C (Tercera falange)
		model = glm::translate(modelTemp, glm::vec3(0.225f, 0.0f, 0.0f)); // Traslada desde la punta de la segunda falange
		model = glm::rotate(model, glm::radians(dedo43), glm::vec3(0.0f, 0.0f, 1.0f)); // Aplica la rotación
		model = glm::translate(model, glm::vec3(0.26f, 0.0f, -0.0f)); // Ajusta la posición después de rotar
		model = glm::scale(model, glm::vec3(0.23f, 0.10f, 0.08f)); // Ajusta el tamaño de la tercera falange
		color = glm::vec3(0.0, 1.0f, 1.0f); // Color cian para diferenciar
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36); // Renderizar la tercera falange

		// Model pulgar1 (Primera falange del pulgar)
		model = glm::translate(modelTemp, glm::vec3(-0.32f, -0.35f, 0.1875f)); // Ajusta su posición más hacia la palma
		model = glm::rotate(model, glm::radians(pulgar1), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación en eje Y en lugar de Z
		modelTemp = model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f)); // Ajuste del pivote
		model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.08f));
		color = glm::vec3(1.0, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Model pulgar2 (Segunda falange del pulgar)
		model = glm::translate(modelTemp, glm::vec3(0.08f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(pulgar2), glm::vec3(0.0f, 1.0f, 0.0f)); // Rotación en eje X para mejor realismo
		modelTemp = model = glm::translate(model, glm::vec3(0.2f, 0.0f, 0.0f)); // Ajuste del pivote
		model = glm::scale(model, glm::vec3(0.225f, 0.10f, 0.08f));
		color = glm::vec3(1.0, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glDrawArrays(GL_TRIANGLES, 0, 36); //E


		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.02f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.02f;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		movY += 0.005f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		movY -= 0.005f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.02f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.02f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && rot <25.0f)
		rot += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && rot > -120.0f)
		rot -= 0.05f;

	// Hombro: -90° a 90°
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && hombro < 90.0f)
		hombro += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && hombro > -90.0f)
		hombro -= 0.05f;

	// Codo: 0° a 135° (solo flexión, no hiperextensión)
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && codo < 0.0f)
		codo += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && codo > -135.0f)
		codo -= 0.05f;

	// Muñeca: -45° a 45°
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS && muneca < 45.0f)
		muneca += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && muneca > -45.0f)
		muneca -= 0.05f;
;

// Dedo 1
if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo11 < 0.0f)
	dedo11 += 0.01f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo11 > -20.0f)
dedo11 -= 0.01f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo12 < 0.0f)
	dedo12 += 0.015f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo12 > -22.0f)
dedo12 -= 0.015f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo13 < 0.0f)
	dedo13 += 0.04f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo13 > -22.0f) 

// Dedo 2
if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo21 < 0.0f)
	dedo21 += 0.005f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo21 > -10.0f)
dedo21 -= 0.005f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo22 < 0.0f)
	dedo22 += 0.007f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo22 > -15.0f)
dedo22 -= 0.007f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo23 < 0.0f)
	dedo23 += 0.008f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo23 > -15.0f)
dedo23 -= 0.008f;

// Dedo 3
if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo31 < 0.0f)
	dedo31 += 0.005f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo31 > -10.0f)
dedo31 -= 0.005f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo32 < 0.0f)
	dedo32 += 0.008f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo32 > -15.0f)
dedo32 -= 0.008f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo33 < 0.0f)
	dedo33 += 0.008f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo33 > -15.0f)
dedo33 -= 0.008f;

// Dedo 4
if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo41 < 0.0f)
	dedo41 += 0.0005f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo41 > -10.0f)
dedo41 -= 0.0005f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo42 < 0.0f)
	dedo42 += 0.0009f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo42 > -15.0f)
dedo42 -= 0.0009f;

if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && dedo43 < 0.0f)
	dedo43 += 0.0008f;
if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && dedo43 > -15.0f)
dedo43 -= 0.0008f;


if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && pulgar1 < -15.0f)  // Se invierte el límite
pulgar1 += 0.5f;  // Se invierte la dirección de la rotación
if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && pulgar1 > 0.0f)
	pulgar1 -= 0.5f;

if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS && pulgar2 < -20.0f)
pulgar2 += 0.8f;
if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS && pulgar2 > 0.0f)
	pulgar2 -= 0.8f;

}