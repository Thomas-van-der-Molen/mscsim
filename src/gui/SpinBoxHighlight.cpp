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

#include <gui/SpinBoxHighlight.h>

#include <QMouseEvent>
#include <QLineEdit>

////////////////////////////////////////////////////////////////////////////////

SpinBoxHighlight::SpinBoxHighlight( QWidget *parent ) :
    QDoubleSpinBox ( parent ),
    _highlighted ( false )
{
    installEventFilter( this );

    QObjectList list = children();

    for ( QObjectList::iterator it = list.begin(); it != list.end(); it++ )
    {
        QLineEdit *lineEdit = qobject_cast< QLineEdit* >( *it );

        if ( lineEdit )
        {
            lineEdit->installEventFilter( this );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

SpinBoxHighlight::~SpinBoxHighlight() {}

////////////////////////////////////////////////////////////////////////////////

void SpinBoxHighlight::setHighlighted( bool highlighted )
{
    _highlighted = highlighted;

    if ( _highlighted )
    {
        setStyleSheet( "QDoubleSpinBox { background-color: #ff9; }" );
    }
    else
    {
        setStyleSheet( "" );
    }
}

////////////////////////////////////////////////////////////////////////////////

void SpinBoxHighlight::toggleHighlight()
{
    setHighlighted( !_highlighted );
}

////////////////////////////////////////////////////////////////////////////////

bool SpinBoxHighlight::eventFilter( QObject *, QEvent *event )
{
    if ( event->type() == QMouseEvent::MouseButtonDblClick )
    {
        toggleHighlight();
    }

    return false;
}
