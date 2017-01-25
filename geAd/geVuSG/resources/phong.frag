#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

layout(binding = 0, set=0) uniform sampler2D tex;

layout(location = 0) out vec4 fragColor;


vec3 lambert(vec3 pos, vec3 norm, vec3 color,
  vec3 lightPos, vec3 ambientLight, vec3 diffuseLight) {
  vec3 N = normalize(norm);
  vec3 L = normalize(lightPos - pos);
  vec3 A = color*ambientLight;
  vec3 D = color*diffuseLight*clamp(dot(N, L), 0, 1);
  return A + D;
}

void main() {
  vec3 color = texture(tex, texCoord).xyz;
  //vec3 color = vec3(1,1,1);
  fragColor = vec4(lambert(position,normal,color,vec3(50,500,50),vec3(0.6),vec3(0.6)), 1);
  //fragColor = vec4(texCoord,0,1);
}
