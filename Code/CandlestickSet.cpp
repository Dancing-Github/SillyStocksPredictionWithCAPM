#include "CandlestickSet.h"

CandlestickSet::CandlestickSet(QObject *parent)
{

}

void CandlestickSet::getHovered()
{
    emit this->toHovered(open(),high(),low(),close(),timestamp());
}
