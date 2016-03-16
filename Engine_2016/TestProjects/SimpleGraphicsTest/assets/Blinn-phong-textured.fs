// default to medium precision
precision mediump float;

#define saturate(x) clamp(x, 0.0, 1.0)

struct MATERIAL
{
	vec4 vAmbient;
	vec4 vDiffuse;
	vec4 vSpecular;
};

uniform MATERIAL g_Material;
uniform sampler2D s_diffuseMap;

varying vec3 g_vViewVecES;
varying vec3 g_vNormalES;
varying vec3 g_vLightVecES;
varying vec2 g_texCoordsOS;

void main()
{
	vec3 vNormal = normalize(g_vNormalES);
	vec3 vLight = normalize(g_vLightVecES);
	vec3 vView = normalize(g_vViewVecES);
	vec3 vHalf = normalize(vLight + vView);

	float NdotL = saturate(dot(vNormal,vLight));
	float NdotH = saturate(dot(vNormal,vHalf));

	//Compute the lighting in eye-space
	float fDiffuse = NdotL;

	float fSpecular = pow(NdotH, g_Material.vSpecular.w);
	float SelfShadow = 4.0 * fDiffuse;

	//Combine lighting with the material properties
	gl_FragColor.rgba = vec4(0.15, 0.15, 0.15, 0.15) * g_Material.vAmbient;
	gl_FragColor.rgba += g_Material.vDiffuse * fDiffuse;
	gl_FragColor.rgb += SelfShadow * vec3(0.15, 0.15, 0.15) * g_Material.vSpecular.xyz * fSpecular;
	
	vec4 texelColor = texture2D(s_diffuseMap, g_texCoordOS);
	gl_FragColor += g_Material.ambientColor * texelColor;
	gl_FragColor += g_Material.diffuseColor * texelColor;
}
