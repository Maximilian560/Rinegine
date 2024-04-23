class RG_EX_GL_Buffers{
    uint GL_VBO = -1;
    RG_Array<double> vbo;

    uint GL_CBO = -1;
    RG_Array<double> cbo;

    uint GL_TBO = -1;
    RG_Array<double> tbo;
    
    RG_Array<uint> ebo;
public:
    void clearArr(){
        vbo.clear();
        cbo.clear();
        tbo.clear();
        ebo.clear();
    }
    
}

class RG_EX_Object{
    POINT3D pos;
    POINT3D size;
    POINT3D rot;
    COLOR4D col;
    double scale = 1;
    int texture = -1;
    bool gui = false;
    LINK_GUI_TYPE guitype = RG_GUI_LINK_NONE;

    RG_EX_GL_Buffers buf;

};