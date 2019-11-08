#ifndef SCENELOADER_H
#define SCENELOADER_H
#include <mainwindow.h>
#include <iostream>
class SceneLoader
{
public:
    SceneLoader();
    ~SceneLoader();
    SceneLoader(const SceneLoader& f);
    void setFilePath(std::string path);
    std::string getFilePath();
    QGraphicsScene* getScene() const;
    bool sceneSave(QGraphicsScene* scene);
    QJsonArray sceneLoad(QString fileName);

private:
    QGraphicsScene* scene;
    std::string filePath;
};

#endif // SCENELOADER_H
