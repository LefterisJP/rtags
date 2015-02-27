/* This file is part of RTags.

RTags is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RTags is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with RTags.  If not, see <http://www.gnu.org/licenses/>. */

#include "DependenciesJob.h"
#include "RTags.h"
#include "Server.h"
#include "FileManager.h"
#include "Project.h"

DependenciesJob::DependenciesJob(const std::shared_ptr<QueryMessage> &query, const std::shared_ptr<Project> &project)
    : QueryJob(query, QuietJob, project)
{
    Path p = query->query();
    p.resolve();
    mFileId = Location::fileId(p);
}

int DependenciesJob::execute()
{
    if (!mFileId)
        return 1;
    std::shared_ptr<Project> proj = project();
    if (!proj)
        return 2;
    write(proj->dumpDependencies(mFileId));
    return 0;
}
