#version 120

//uniform float time;
//const float change = 0.076;
//float percent = mod(time*0.079, 10.0*change);


uniform float time;
uniform float percent;


void main() {
    
//    vec4 colorRight = vec4(1.0, 0.0, 1.0, 1.0);
    vec4 colorRight = vec4(0.0289, 0.0, 0.05, 1.0);
    vec4 colorLeft = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 colorMix;
    
    colorMix = mix(colorRight, colorLeft, percent);
    
    gl_FragColor = colorMix;
    
// From the original example
//    float windowWidth = 1024.0;
//    float windowHeight = 768.0;
//	float r = gl_FragCoord.x;
//	float g = 0.0;
//	float b =  gl_FragCoord.y;
//	float a = 1.0;
//	gl_FragColor = mix(r, b, a);
    
}