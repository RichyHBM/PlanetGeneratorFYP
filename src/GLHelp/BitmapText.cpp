
#include "BitmapText.hpp"
#include <glm/gtx/transform2.hpp>

BitmapText::BitmapText()
{


    std::string vertexShader =
        "#version 120\n"
        "uniform mat4 MVP;\n"
        "attribute vec4 Position;\n"
        "attribute vec2 UV;\n"
        "varying vec2 uv;\n"

        "void main(){\n"
        "uv = UV;\n"
        "gl_Position =  MVP * Position;\n"
        "}";

    std::string fragmentShader =
        "#version 120\n"
        "varying vec2 uv;\n"
        "uniform sampler2D Texture;\n"
        "uniform vec4 Color;\n"
        "void main(){\n"
        "vec4 textur = texture2D( Texture, uv ).rgba;\n"
        "textur.rgb = Color.rgb;\n"
        "if(textur.a == 0.0f){\n"
        "textur = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
        "}\n"
        "gl_FragColor = textur;\n"
        "}";
    mShader.LoadShaderCode(vertexShader ,fragmentShader);

    mPosition = glm::vec3(0.0f);
    mMVP = glm::mat4(1.0f);
    mOrtho = NULL;

    mColor = glm::vec4(1.0f);

    mText = "text";


    mVertexBuffer.SetAttributeIndex(mShader.GetAttribute( "Position" ));
    mUVBuffer.SetAttributeIndex(mShader.GetAttribute( "UV" ));

}

BitmapText::~BitmapText()
{

}

void BitmapText::LoadFile(const std::string& pImageFile, const std::string& pUVFile )
{
    mBitmap.LoadFromFile(pImageFile.c_str());

    mBitmap.Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);
    Texture::Unbind();

    std::ifstream myfile;

    try
    {
        myfile.open(pUVFile.c_str());
        if (myfile.is_open())
        {
            while ( myfile.good() )
            {
                std::string line;
                std::getline (myfile,line);

                float x,y,z,w;

                std::stringstream strx, stry, strz, strw;

                strx << line[0]     << line[1]  << line[2]  << line[3];
                stry << line[5]     << line[6]  << line[7]  << line[8];
                strz << line[10]    << line[11] << line[12] << line[13];
                strw << line[15]    << line[16] << line[17] << line[18];

                strx  >> x;
                stry  >> y;
                strz  >> z;
                strw  >> w;

                mPositions.push_back(glm::vec4(x, y, z, w));

            }
            myfile.close();
        }
        Rebuild();
    }
    catch(const std::exception &exc)
    {
        std::cout << "Failed to load: " << pUVFile << std::endl;
        std::cerr << exc.what();
    }


}

void BitmapText::SetText(const std::string& pText)
{
    mText = pText;
    Rebuild();
}

void BitmapText::SetPosition(const glm::vec2& pPosition)
{
    mPosition = glm::vec3(pPosition.x, pPosition.y, 0.0f);
    if(mOrtho != NULL)
        mMVP = (*mOrtho) * glm::translate(glm::mat4(1.0f), mPosition);
}

void BitmapText::SetOrtho(glm::mat4 &pOrtho)
{
    mOrtho = &pOrtho;
    mMVP = (*mOrtho) * glm::translate(glm::mat4(1.0f), mPosition);
}

void BitmapText::Draw()
{


    mShader.Bind();
    glUniformMatrix4fv(mShader.GetUniform ("MVP"), 1, GL_FALSE, &mMVP[0][0]);

    glActiveTexture(GL_TEXTURE0);
    mBitmap.Bind();
    glUniform1i(mShader.GetUniform ("Texture"), 0);

    glUniform4fv(mShader.GetUniform ("Color"),1 , &mColor[0]);

    mVertexBuffer.Bind(3);
    mUVBuffer.Bind(2);

    glDrawArrays(GL_TRIANGLES, 0, mText.size() * 6);

    mUVBuffer.Unbind();
    mVertexBuffer.Unbind();

    Texture::Unbind();
    Shader::Unbind();

}

void BitmapText::Rebuild()
{
    mVertexList.clear();
    mUVList.clear();

    float disp = 0.0f;
    float largestHeight = 0.0f;
    for(unsigned int i = 0; i < mText.size(); i++)
    {
        glm::vec4 charRect = mPositions[mText[i]];
        if(largestHeight < charRect.w) largestHeight = charRect.w;


        mVertexList.push_back(0.0f + disp);
        mVertexList.push_back(0.0f);
        mVertexList.push_back(0.0f);

        mVertexList.push_back(0.0f + disp);
        mVertexList.push_back(charRect.w);
        mVertexList.push_back(0.0f);

        mVertexList.push_back(charRect.z + disp);
        mVertexList.push_back(0.0f);
        mVertexList.push_back(0.0f);

        mVertexList.push_back(charRect.z + disp);
        mVertexList.push_back(0.0f);
        mVertexList.push_back(0.0f);

        mVertexList.push_back(0.0f + disp);
        mVertexList.push_back(charRect.w);
        mVertexList.push_back(0.0f);


        mVertexList.push_back(charRect.z + disp);
        mVertexList.push_back(charRect.w);
        mVertexList.push_back(0.0f);



        mUVList.push_back(charRect.x / mBitmap.GetSize().x);
        mUVList.push_back(charRect.y / mBitmap.GetSize().y);

        mUVList.push_back(charRect.x / mBitmap.GetSize().x);
        mUVList.push_back((charRect.y + charRect.w) / mBitmap.GetSize().y);

        mUVList.push_back((charRect.x + charRect.z ) / mBitmap.GetSize().x);
        mUVList.push_back(charRect.y / mBitmap.GetSize().y);

        mUVList.push_back((charRect.x + charRect.z ) / mBitmap.GetSize().x);
        mUVList.push_back(charRect.y / mBitmap.GetSize().y);

        mUVList.push_back(charRect.x / mBitmap.GetSize().x);
        mUVList.push_back((charRect.y + charRect.w) / mBitmap.GetSize().y);

        mUVList.push_back((charRect.x + charRect.z ) / mBitmap.GetSize().x);
        mUVList.push_back((charRect.y + charRect.w) / mBitmap.GetSize().y);

        disp += charRect.z;
    }


    mVertexBuffer.AddData(mVertexList, sizeof(GLfloat), GL_ARRAY_BUFFER, GL_STREAM_DRAW);

    mUVBuffer.AddData(mUVList, sizeof(GLfloat), GL_ARRAY_BUFFER, GL_STREAM_DRAW);

}

void BitmapText::SetColor(float pRed , float pGreen, float pBlue , float pAlpha)
{
    mColor.x = pRed;
    mColor.y = pGreen;
    mColor.z = pBlue;
    mColor.w = pAlpha;
}
