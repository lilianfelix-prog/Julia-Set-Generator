#version 430

#define GOL_WIDTH 768

#version 330 core

// Uniform inputs
uniform vec2 u_resolution;  // Viewport resolution
uniform float u_time;       // Optional: for animation
uniform float u_cx;         // Constant x for Julia set
uniform float u_cy;         // Constant y for Julia set
uniform float u_radius;     // Escape radius

// Output color
out vec4 fragColor;

void main() {
    // Normalize pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / u_resolution.xy;
    
    // Scale and center coordinates to match original code
    float R = 1.2;
    float zx = uv.x * (2.0 * R) - R;
    float zy = uv.y * (2.0 * R) - R;
    
    // Julia set parameters (equivalent to cx, cy in original code)
    float cx = 0.7885 * cos(u_time);
    float cy = 0.7885 * sin(u_time);
    
    // Iteration parameters
    int max_iteration = 50;
    int iteration = 0;
    
    // Julia set iteration
    while ((zx * zx) + (zy * zy) < R * R && iteration < max_iteration) {
        float temp = (zx * zx) - (zy * zy);
        zy = 2.0 * zx * zy + cy;
        zx = temp + cx;
        
        iteration++;
    }
    
    // Color selection
    vec3 color1 = vec3(1.0, 1.0, 1.0);  // White
    vec3 color2 = vec3(0.0, 0.0, 0.545);  // Dark Blue
    
    // Coloring logic
    if (iteration == max_iteration) {
        // Inside the set
        fragColor = vec4(color1, 1.0);
    } else {
        // Outside the set - create gradient
        float brightness = float(iteration) / float(max_iteration);
        vec3 gradientColor = color2 + vec3(brightness);
        
        fragColor = vec4(gradientColor, 1.0);
    }
}