/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <gui/Locations.h>

#include <QFile>

#include <fdmUtils/fdm_Units.h>

////////////////////////////////////////////////////////////////////////////////

Locations* Locations::m_instance = 0;

////////////////////////////////////////////////////////////////////////////////

Locations::Locations()
{
    QFile file( "data/gui/locations.xml" );

    if ( file.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;

        doc.setContent( &file, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "locations" )
        {
            QDomElement locationNode = rootNode.firstChildElement( "location" );

            while ( !locationNode.isNull() )
            {
                parseLocation( locationNode );
                locationNode = locationNode.nextSiblingElement( "location" );
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

Locations::~Locations() {}

////////////////////////////////////////////////////////////////////////////////

void Locations::parseLocation(const QDomElement &node )
{
    QDomElement nameNode = node.firstChildElement( "name" );

    QDomElement latNode = node.firstChildElement( "lat" );
    QDomElement lonNode = node.firstChildElement( "lon" );
    QDomElement altNode = node.firstChildElement( "alt" );
    QDomElement hdgNode = node.firstChildElement( "hdg" );

    if ( !nameNode.isNull()
      && !latNode.isNull()
      && !lonNode.isNull()
      && !altNode.isNull()
      && !hdgNode.isNull() )
    {
        Location location;

        location.name = nameNode.text();

        location.lat = fdm::Units::deg2rad( latNode.text().toFloat() );
        location.lon = fdm::Units::deg2rad( lonNode.text().toFloat() );
        location.alt = altNode.text().toFloat();
        location.hdg = fdm::Units::deg2rad( hdgNode.text().toFloat() );

        m_locations.push_back( location );
    }
}