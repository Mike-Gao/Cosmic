#version 110
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect posData;
uniform sampler2DRect radiData; 
uniform sampler2DRect accData;

uniform float resolution; 
uniform float limit; 

varying vec2 texcoord;	

void main()
{    
	vec3 pos =  texture2DRect( posData,  texcoord ).xyz;    
 	vec3 radi =  texture2DRect( radiData,  texcoord ).xyz;    
    vec3 acc =  texture2DRect( accData,  texcoord ).xyz;
       	     
   	vec3 force = vec3(0.0, 0.0, 0.00);
    
    float i = 0.0; 
    float j = 0.0;     
    
    for(i = 0.0; i < resolution; i++)
    {
        for(j = 0.0; j < resolution; j++)
        {   
    		vec2 coord = vec2(i, j);                         
            vec3 otherPos = texture2DRect( posData, coord ).xyz; 
            vec3 direction = otherPos - pos; 
            float dist = length(direction);
            if(dist > 0.0001)
            {
                vec3 otherRadi = texture2DRect( radiData,  coord ).xyz;
                float charge = radi.x*otherRadi.x; 
                direction = normalize(direction); 
                dist = dist*dist;                  
                force += (charge/dist)*direction;             
            }
        }
    }
    
	float m = length(force); 
	if(m > limit)
	{
		force = normalize(force)*limit; 
	}
    
  	gl_FragColor = vec4(acc-force, 1.0); 
}