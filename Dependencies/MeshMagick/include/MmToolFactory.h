/*
This file is part of MeshMagick - An Ogre mesh file manipulation tool.
Copyright (C) 2007-2009 Daniel Wickert

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifndef __MM_MESHTOOL_FACTORY_H__
#define __MM_MESHTOOL_FACTORY_H__

#include "MeshMagickPrerequisites.h"

#include "MmOptionsParser.h"

namespace meshmagick
{
    class _MeshMagickExport ToolFactory
    {
    public:
        virtual Tool* createTool() = 0;
        virtual void destroyTool(Tool* tool) = 0;

        virtual OptionDefinitionSet getOptionDefinitions() const = 0;

        // Returns the name of the tool this factory creates.
        virtual Ogre::String getToolName() const = 0;

        // Returns a short description of the tool this factory creates.
        virtual Ogre::String getToolDescription() const = 0;

        virtual void printToolHelp(std::ostream& out) const = 0;
    };
}
#endif
