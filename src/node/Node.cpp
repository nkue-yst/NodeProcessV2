/**********
 * Author:  Y.Nakaue
 * Created: 2023/04/08
 * Edited:  2023/04/09
 **********/

#include "Node.h"

#include "Pin.h"

Node::Node()
    : m_id(0)
    , m_name("none")
{
}

Node::~Node()
{
}

void Node::draw()
{
    this->drawInPins();
    this->drawOutPins();

    this->drawContent();
}

void Node::drawInPins()
{

}

void Node::drawOutPins()
{

}
