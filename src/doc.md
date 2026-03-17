packet:
	type: 1B
	channel: 16B // only in request
	data: ...
	
types:
	'W':  // write
		channel : 16B
  	data:
   		message : 1000B
			
  'R': // read 
  	channel : 16B

	'r': // read response
		channel : 16B
  	data:
   		message : 1000B
