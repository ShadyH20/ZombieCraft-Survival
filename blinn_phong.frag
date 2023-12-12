#version 110

uniform sampler2D colorMap;
uniform float materialAlpha;

varying vec3 normal;

void main()
{   
    vec3 n = normalize(normal);

    float nDotL = max(0.0, dot(n, gl_LightSource[0].position.xyz));
    float nDotH = max(0.0, dot(normal, vec3(gl_LightSource[0].halfVector)));
    float power = (nDotL == 0.0) ? 0.0 : pow(nDotH, gl_FrontMaterial.shininess);
    
    vec4 ambient = gl_FrontLightProduct[0].ambient;
    vec4 diffuse = gl_FrontLightProduct[0].diffuse * nDotL;
    vec4 specular = gl_FrontLightProduct[0].specular * power;
    vec4 color = gl_FrontLightModelProduct.sceneColor + ambient + diffuse + specular;
    
    gl_FragColor = color * texture2D(colorMap, gl_TexCoord[0].st);
    gl_FragColor.a = materialAlpha;
}