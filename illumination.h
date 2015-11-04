#ifndef illumination_H
#define illumination_H

void setLightScourcePosX(float x);

void setLightScourcePosY(float y);

void setLightScourcePosZ(float z);

void setLightScourceIntens(float r, float g, float b);

void setAmbientLightIntens(float r, float g, float b);

void setMaterialAmbientCoeffR(float r);

void setMaterialAmbientCoeffG(float g);

void setMaterialAmbientCoeffB(float b);

void setMaterialDiffuseCoeffR(float r);

void setMaterialDiffuseCoeffG(float g);

void setMaterialDiffuseCoeffB(float b);

void setMaterialSpecularCoeffR(float r);

void setMaterialSpecularCoeffG(float g);

void setMaterialSpecularCoeffB(float b);

void setPhongShininess(int shininess);

void flipNormals();

#endif
