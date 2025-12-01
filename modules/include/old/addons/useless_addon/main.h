#pragma once
#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "add/useless-add"
namespace RGU{

template<class type>
void printhex(type in){
    char* b = (char*)&in;
    for(int i = sizeof(type)-1; i>=0;i--){
        rg_cout<<hex<<(int)*(b+i)<<" ";
    }rg_cout<<endl;
}

/*template<class to, class from>
to convert_hex(from in){
    to out;
    char* a = (char*)&in;
    char* b = (char*)&out;
    /*for(int i = (sizeof(from)-1-rg_max(0,int(sizeof(to))-int(sizeof(from)))); i>=rg_max(0,sizeof(from)-sizeof(to));i--){
        //rg_cout<<i<<" "<<rg_max(0,int(sizeof(to))-int(sizeof(from)))<<endl; 
        b[i]=a[i];
    }* /
    return out;
}*/

};