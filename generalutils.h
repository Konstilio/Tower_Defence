#ifndef GENERALUTILS_H
#define GENERALUTILS_H

#include <QSize>
#include <QPixmap>

class GeneralUtils
{
public:
    static GeneralUtils& Instance();

    QPixmap TiledRedTowerPixmap();

    QSize GameViewSize() const;
    int TileSize() const;

private:
    QSize mp_GameViewSize;
    int mp_TileSize;

    QPixmap mp_TiledRedTowerPixmap;

    GeneralUtils();
    GeneralUtils(const GeneralUtils& Other) = delete;
    GeneralUtils& operator=(const GeneralUtils& Other) = delete;

};

#endif // GENERALUTILS_H
