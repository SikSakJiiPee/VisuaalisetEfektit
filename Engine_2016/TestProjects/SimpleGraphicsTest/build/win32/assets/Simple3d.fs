// default to medium precision
precision mediump float;
#ifdef GL_FRAGMENT_PRECISION_HIGH
	#define NEED_HIGHP highp
#else
	#define NEED_HIGHP mediump
#endif


void main()
{
	gl_FragColor.rbga = vec4(1.0f, 0.2f, 0.5f, 1.0f);
}