#version 130

#ifdef GL_FRAGMENT_PRECISION_HIGH
			precision highp float;
			#else
			   precision mediump float;
			#endif

			varying   vec4 g_vVSColor;                                          
			varying   vec2 g_vVSTexCoord;                                       
			
			uniform float totalTime;
																				 
			void main()														 
			{																	 
			    float x = 256*g_vVSTexCoord.x;
			    float y = 256*g_vVSTexCoord.y;
			    float t = totalTime; 
			    float v = 0.0;
			    v += 0.5 + (0.5 * sin(x/7.0+t));
			    v += 0.5 + (0.5 * sin(y/5.0-t));
			    v += 0.5 + (0.5 * sin((x+y)/6.0-t));
				v += 0.5 + (0.5 * sin(sqrt((x*x + y*y))/4.0-t));
			    v = 0.25 * tan(2*v);
			    gl_FragColor = vec4(v,v*g_vVSTexCoord.x,v*g_vVSTexCoord.y,1.0);     
			}