#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COURSES 50

typedef struct {
    char id[20];
    char name[100];
} Course;

typedef struct {
    int numCourses;
    Course allCourses[MAX_COURSES];
    int childCourses[MAX_COURSES][MAX_COURSES];
} CourseLibrary;

CourseLibrary courseLibrary;

void initializeCourseLibrary() 
{
    courseLibrary.numCourses = 0;
    for (int i = 0; i < MAX_COURSES; i++) {
        courseLibrary.allCourses[i].id[0] = '\0';
        courseLibrary.allCourses[i].name[0] = '\0';
        for (int j = 0; j < MAX_COURSES; j++) {
            courseLibrary.childCourses[i][j] = 0;
        }
    }
}

void addCourse(const char* id, const char* name) 
{
    if (courseLibrary.numCourses < MAX_COURSES) 
    {
        strcpy_s(courseLibrary.allCourses[courseLibrary.numCourses].id, sizeof(courseLibrary.allCourses[courseLibrary.numCourses].id), id);
        strcpy_s(courseLibrary.allCourses[courseLibrary.numCourses].name, sizeof(courseLibrary.allCourses[courseLibrary.numCourses].name), name);
        courseLibrary.numCourses++;
    }
}

void addPrerequisite(const char* parent, const char* child) {
    int parentIndex = -1;
    int childIndex = -1;

    for (int i = 0; i < courseLibrary.numCourses; i++) {
        if (strcmp(courseLibrary.allCourses[i].id, parent) == 0) {
            parentIndex = i;
        }
        if (strcmp(courseLibrary.allCourses[i].id, child) == 0) {
            childIndex = i;
        }
    }

    if (parentIndex != -1 && childIndex != -1)
    {
        courseLibrary.childCourses[parentIndex][childIndex] = 1;
    }
}

void DPS(int courseIndex, bool visited[], char stack[MAX_COURSES][20], int* stackIndex) {
    visited[courseIndex] = true;

    for (int i = 0; i < courseLibrary.numCourses; i++) {
        if (!visited[i] && courseLibrary.childCourses[courseIndex][i] != 0) {
            DPS(i, visited, stack, stackIndex);
        }
    }

    strcpy_s(stack[(*stackIndex)], sizeof(stack[(*stackIndex)]), courseLibrary.allCourses[courseIndex].id);
    (*stackIndex)++;
}

void topologicalSort() {
    bool visited[MAX_COURSES];
    char stack[MAX_COURSES][20];
    int stackIndex = 0;

    for (int i = 0; i < courseLibrary.numCourses; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < courseLibrary.numCourses; i++) {
        if (!visited[i]) {
            DPS(i, visited, stack, &stackIndex);
        }
    }

    printf("============================================\n");
    printf("           List OF all Courses\n");
    printf("============================================\n");

    for (int i = stackIndex - 1; i >= 0; i--) {
        int courseIndex = -1;
        for (int j = 0; j < courseLibrary.numCourses; j++) {
            if (strcmp(courseLibrary.allCourses[j].id, stack[i]) == 0) {
                courseIndex = j;
                break;
            }
        }

        if (courseIndex != -1) {
            int depth = 0;
            for (int j = 0; j < depth; j++) {
                printf("|  ");
            }
            printf("|-> %s - %s\n", courseLibrary.allCourses[courseIndex].id, courseLibrary.allCourses[courseIndex].name);

            for (int j = 0; j < courseLibrary.numCourses; j++) {
                if (courseLibrary.childCourses[courseIndex][j] != 0) {
                    depth++;
                    i--;
                    j = -1; 
                }
            }
        }
    }

    printf("============================================\n");
}
void recursiveDisplay(const char* course, int level) {
    int courseIndex = -1;
    for (int i = 0; i < courseLibrary.numCourses; i++) {
        if (strcmp(courseLibrary.allCourses[i].id, course) == 0) {
            courseIndex = i;
            break;
        }
    }

    if (courseIndex != -1) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }

        printf("|-> %s - %s", courseLibrary.allCourses[courseIndex].id, courseLibrary.allCourses[courseIndex].name);
        printf("\n");

        for (int i = 0; i < courseLibrary.numCourses; i++) {
            if (courseLibrary.childCourses[courseIndex][i] != 0) {
                recursiveDisplay(courseLibrary.allCourses[i].id, level + 1);
            }
        }
    }
}

void displayAll() {
    printf("============================================\n");
    printf("           List OF all Courses\n");
    printf("============================================\n");

    for (int i = 0; i < courseLibrary.numCourses; i++) {
        if (courseLibrary.childCourses[i][i] == 0) {
            recursiveDisplay(courseLibrary.allCourses[i].id, 0);
            printf("============================================\n");

        }
    }

    printf("============================================\n");
}



int main() {
    initializeCourseLibrary();

    addCourse("CS 1411", "Programming Principles I");
    addCourse("MATH 1451", "Calculus I with Applications");
    addCourse("ENGL 1301", "Essentials of College Rhetoric");
    addCourse("CS 1412", "Programming Principles II");
    addCourse("MATH 1452", "Calculus II with Applications");
    addCourse("PHYS 1408", "Principles of Physics I");
    addCourse("ENGL 1302", "Advanced College Rhetoric");
    addCourse("CS 2413", "Data Structures");
    addCourse("CS 1382", "Discrete Computational Structures");
    addCourse("ECE 2372", "Modern Digital System Design");
    addCourse("MATH 2450", "Calculus III with Applications");
    addCourse("PHYS 2401", "Principles of Physics II");
    addCourse("CS 2350", "Computer Organization and Assembly Language Programming");
    addCourse("CS 2365", "Object-Oriented Programming");
    addCourse("ENGR 2392", "Engineering Ethics and Its Impact on Society");
    addCourse("POLS 1301", "American Government");
    addCourse("MATH 2360", "Linear Algebra");
    addCourse("ENGL 2311", "Introduction to Technical Writing");
    addCourse("CS 3361", "Concepts of Programming Languages");
    addCourse("CS 3364", "Design and Analysis of Algorithms");
    addCourse("MATH 3342", "Mathematical Statistics for Engineers and Scientists");
    addCourse("POLS 2306", "Texas Politics and Topics");
    addCourse("CS 3365", "Software Engineering I");
    addCourse("CS 3375", "Computer Architecture");
    addCourse("CS 3383", "Theory of Automata");
    addCourse("CS 4365", "Software Engineering II");
    addCourse("CS 4352", "Operating Systems");
    addCourse("CS 4354", "Concepts of Database Systems");
    addCourse("CS 4366", "Senior Capstone Project");


    addPrerequisite("CS 1412", "CS 1411");
    addPrerequisite("MATH 1452", "MATH 1451");
    addPrerequisite("PHYS 1408", "MATH 1451");
    addPrerequisite("ENGL 1302", "ENGL 1301");
    addPrerequisite("CS 2413", "CS 1412");
    addPrerequisite("CS 1382", "CS 1411");
    addPrerequisite("ECE 2372", "MATH 1451");
    addPrerequisite("MATH 2450", "MATH 1452");
    addPrerequisite("PHYS 2401", "PHYS 1408");
    addPrerequisite("CS 2350", "CS 1412");
    addPrerequisite("CS 2350", "ECE 2372");
    addPrerequisite("CS 2365", "CS 2413");
    addPrerequisite("MATH 2360", "MATH 1452");
    addPrerequisite("ENGL 2311", "ENGL 1301");
    addPrerequisite("ENGL 2311", "ENGL 1302");
    addPrerequisite("CS 3361", "CS 2413");
    addPrerequisite("CS 3364", "CS 2413");
    addPrerequisite("CS 3364", "CS 1382");
    addPrerequisite("CS 3364", "MATH 2360");
    addPrerequisite("MATH 3342", "MATH 2450");
    addPrerequisite("CS 3365", "CS 2365");
    addPrerequisite("CS 3365", "CS 2413");
    addPrerequisite("CS 3365", "MATH 3342");
    addPrerequisite("CS 3375", "CS 2350");
    addPrerequisite("CS 3383", "CS 1382");
    addPrerequisite("CS 4365", "CS 3365");
    addPrerequisite("CS 4352", "CS 3364");
    addPrerequisite("CS 4352", "CS 3375");
    addPrerequisite("CS 4354", "CS 3364");
    addPrerequisite("CS 4366", "CS 4365");

    displayAll();

    return 0;
}