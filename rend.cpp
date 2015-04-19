void mainImage(vec3 fragColor, vec2 fragCoord)
{
	ComputeBoatTransform();
	
	vec2 camRot = vec2(.5,.5)+vec2(-.35,4.5)*(iMouse.yx/iResolution.yx);
	vec3 pos, ray;
	CamPolar( pos, ray, vec3(0), camRot, 3.0, 1.0, fragCoord );
	
	float to = TraceOcean( pos, ray );
	float tb = TraceBoat( pos, ray );
	
	vec3 result;
	if ( to > 0.0 && ( to < tb || tb == 0.0 ) )
		result = ShadeOcean( pos+ray*to, ray, fragCoord );
	else if ( tb > 0.0 )
		result = ShadeBoat( pos+ray*tb, ray );
	else
		result = Sky( ray );
	
	// vignette effect
	result *= 1.1*smoothstep( .35, 1.0, localRay.z );
	
	fragColor = ToGamma(result);
}