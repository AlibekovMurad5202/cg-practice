#version 430

in vec3 vertex;
out vec3 interpolated_vertex;

void main()
{
	gl_Position = vec4(vertex, 1.f);
	interpolated_vertex = vertex;
}