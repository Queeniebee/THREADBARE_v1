#version 120

////uniform float time;
//uniform float percent;
uniform float alpha;


void main() {


//    TEST COLOR
//    vec4 colorRight = vec4(1.0, 0.0, 1.0, 1.0);
    
    // The right color
//    vec4 colorRight = vec4(0.0289, 0.0, 0.05, 1.0);
        
//    vec4 colorLeft = vec4(0.0, 0.0, 0.0, 1.0);
//    vec4 colorMix;
    vec4 colorMix = vec4(0.0, 0.0, 0.0, alpha);
////    colorMix = mix(colorRight, colorLeft, percent);
//
//    colorMix.ga = vec2(0.0, alpha);
    gl_FragColor = colorMix;
    
}