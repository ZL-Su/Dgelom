#SIMD Support

#Begin: 
>>load numerical values into packed type dgelom::simd::Packet_<type, num_of_values>, type can be float, double, or...
  1. from a scalar value: for example, set a "_val" (float-type) into 256 bits register with float type (256/64 float values), do it as follows  
     dgelom::simd::Packet_<float, 4> packed(_val);
   or, 
     dgelom::simd::Packet_<float, 4> packed; 
     packed = _val;
  2. from a set of scalar values: for example, set "_val0, _val1, _val2, _val3" (float-type) into 256 bits register with float type (256/64 float values), do it as follows  
     dgelom::simd::Packet_<float, 4> packed{_val0, _val1, _val2, _val3};
  or, 
     dgelom::simd::Packet_<float, 4> packed; 
     packed = {_val0, _val1, _val2, _val3};
  3. from memory: for example, load "float _data[4] = {...}" into 256 bits register with float type (256/64 float values), do it as follows
     dgelom::simd::Packet_<float, 4> packed(_data);
  or, 
     dgelom::simd::Packet_<float, 4> packed; 
     packed = _data;
>>store from a packet (register) to memory, the only way I have implemented for retrieving data from register. For example, "(float*)data" is a pointer point to a memory block which at least stores 4 single floating points, then the data can be obtained as
     packed.unpack(data);
