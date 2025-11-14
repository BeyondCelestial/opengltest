#version 330 core
layout(location = 0) in vec2 aPos;

vec2 offset;

vec2 off0 = vec2(0.0, 0.0);
vec2 off1 = vec2(0.0, 0.0);
vec2 off2 = vec2(0.0, 0.0);

uniform vec2 offU;

void main() {
    if (gl_VertexID == 0) {
        offset = aPos+off0;

    } else if (gl_VertexID == 1) {
        offset = aPos+off1;

    } else if (gl_VertexID == 2) {
        offset = aPos+off2;
        
    }

    offset =+ offU;
    
    gl_Position = vec4(offset, 0.0, 1.0);
}
