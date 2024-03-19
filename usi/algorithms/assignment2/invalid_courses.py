"""
AUTHOR:     Jeferson Morales Mariciano
PROBLEM:    Verify validity of a set of courses.
INPUT:
    List of courses, each with its prerequisites.
    Each course is listed on a line of input with the following format: COURSE_NAME:{COURSE_NAME, ...}
    The list of prerequisites may be empty.
    The prerequisites for a course C are courses that must be passed before course C can be taken.

VALID:
    It must be possible to take the course and its prerequisites within 5 years, 10 semester program.
INVALID:
    - There can't be a chain of > 10 consecutive prerequisites.
    - Can't take > 60 courses in total, each course can't have > 59 direct or indirect prerequisites.
    - Course with circular chain of prerequisites
    - Course with even a single invalid prerequisite (direct or indirect).

ASSUMPTIONS:
    A course can't be repeated as main course in more than 1 line.
    A course present in a dependency and never more, is considered non-existing and make its dependent courses invalid.
    There can be multiple unconnected graphs within the structure.

STRATEGY:
    - All collections used could be done with plain arrays and integer indexes, such approach has not been used
        in order to show familiarity with data structures (hashset: set(), hashmap: dict)
    - An approach would be DFS, exploring the graph and keeping track foreach node the depth, [un]directed connections,
        and mark properly if a cycle is present. I choose if a cycle is present, not only to include such course in an
        invalid list of courses, but also to mark its connections and depth to MAX_VALUES defined below in order to
        increase security.
    - Since we don't explore again nodes already visited, but in order to know the [un]directed connected nodes, we need
        to store such number foreach node in a collection so when we reach an already visited node, we don't visit again
        that path but look for its values to increase the current parent node ones.
"""
from sys import stdin

MAX_CONSECUTIVE_PREREQUISITES = 9
MAX_COURSES = 60    # max 59 direct or indirect prerequisites per course
INFINITE_DISTANCE = MAX_CONSECUTIVE_PREREQUISITES + 1 + 1   # max chain of prereqs and node holding them + 1 to overflow

SPLIT_COURSE = ':'
SPLIT_PREREQUISITE = ','
TRIM = '\n '


def main() -> None:
    courses = []           # vertex : [string, ...]
    prerequisites = []   # adjacency list : [[string, string, ...], ...]
    map_course_idx = {}    # index: name --> vertex_id {'string', int}

    distances = []  # global weights  idx and indirect visited sign, also indirect invalid sign -> [int]
    relations = []  # global indirect/direct relations -> [int]
    traversing = []  # traversing array tracker -> [bool]

    # input #####################################################################
    for line in stdin:
        # initializations node data track as arrays
        distances.append(0)
        relations.append(0)
        traversing.append(False)
        
        # input handling
        course_prereq = line.split(SPLIT_COURSE)
        course = course_prereq[0]
        prereq_str = course_prereq[1].strip(TRIM)
        prereq_names = prereq_str.split(SPLIT_PREREQUISITE) if prereq_str else []
        courses.append(course)
        prerequisites.append(prereq_names)
        map_course_idx[course] = len(courses) - 1

    # foreach non-visited node, do dfs() #########################################
    for i in range(len(courses)):
        if not distances[i]:
            dfs(prerequisites, i, map_course_idx, distances, traversing, relations)

    # print result ###############################################################
    print('\n'.join(courses[i] for i, dist in enumerate(distances) if dist == INFINITE_DISTANCE), end='')


def dfs(adj: list, node: int, map_courses: dict, distances: list, traversing: list, relations: list) -> None:
    """
    Traverse the graph doing dfs,
    once reached the maximum depth of the dfs, when returning:
    - updates distance value for that particular node.
    - if a node is invalid, it set its distance to INFINITE value
    - update the visited array
        :param adj: Adjacency list to represent graph
        :param node: Current node explored
        :param map_courses: Map courses to int index. {str : int)
        :param distances: List containing max reachable depth of node by index
        :param traversing: Array containing the nodes currently traversed.
        :param relations: Array to keep track of undirected/directed connected nodes
    """
    traversing[node] = True
    max_depth = 0
    total_relations = 0

    # foreach neighbor: string
    for neighbor in adj[node]:
        if neighbor not in map_courses:
            # invalid because the course isn't in available courses to be taken
            distances[node] = INFINITE_DISTANCE
            return
        else:
            # index neighbor
            idx_neighbor = map_courses[neighbor]
            # if neighbor invalid because of depth or for already traversed (cycle), mark node invalid and return
            if (distances[idx_neighbor] == INFINITE_DISTANCE or
                    (traversing[idx_neighbor] and not distances[idx_neighbor])):
                distances[node] = INFINITE_DISTANCE
                return

            # if the node has not been visited, do dfs()
            elif not distances[idx_neighbor]:
                dfs(adj, idx_neighbor, map_courses, distances, traversing, relations)

            # update values of max depth of chains dependencies and total [un]direct connected nodes
            max_depth = max_depth if max_depth > distances[idx_neighbor] else distances[idx_neighbor]
            total_relations += relations[idx_neighbor]
            # if values above limits, mark as invalid and return
            if total_relations >= MAX_COURSES or max_depth == INFINITE_DISTANCE:
                distances[node] = INFINITE_DISTANCE
                return
            
    # update depth, relations, traversing and check validity of dependencies (neighbors)
    distances[node] = 1 + max_depth
    relations[node] = 1 + total_relations
    traversing[node] = False
    # check validity of depth and relations connectivity
    if relations[node] > MAX_COURSES:
        distances[node] = INFINITE_DISTANCE


if __name__ == '__main__':
    main()
