#version 450
// Normal-lit textured vertex stage (original work, no license encumbrance).
// TexVertex layout: pos(3 f32) + normal(3 f32) + uv(2 f32) = 32 bytes.
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUv;
layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec2 fragUv;
void main() {
  gl_Position = vec4(inPos, 1.0);
  fragNormal = inNormal;
  fragUv = inUv;
}
