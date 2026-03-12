packet:
	type: 1B
	xid: 1B
	channel: 16B // only in request
	data: ...
	
types:
	'W':  // write
		data:
			msg: 1000B
			
  'R': // read 
  	data:
   		8B message index (if -1, last message)
  
  'L': // list
  	data: None

	'r':
		data:
			msg: 1000B
	
	'l':
		data:
			number of message (8 Bytes)
