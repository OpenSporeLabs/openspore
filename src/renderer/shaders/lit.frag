#version 450
// Normal-lit textured fragment stage (original work, no license encumbrance).
// Push constant = vec4(lightDir.xyz, ambient). Samples the bound texture.
layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec2 fragUv;
layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 0) uniform sampler2D uTex;
layout(push_constant) uniform Push {
  vec4 light; // xyz = normalized light dir, w = ambient
} push;
void main() {
  vec4 texel = texture(uTex, fragUv);
  vec3 L = normalize(push.light.xyz);
  float ndotl = max(dot(normalize(fragNormal), L), 0.0);
  float light = push.light.w + ndotl;
  outColor = vec4(texel.rgb * light, texel.a);
}
