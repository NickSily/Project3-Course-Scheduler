from bs4 import BeautifulSoup
import requests

url = "https://catalog.ufl.edu/UGRD/courses/computer_and_information_science_and_engineering/"

response = requests.get(url)

page = BeautifulSoup(response.content, 'html.parser')

# print(courseCatalog.prettify())

courses = page.find_all("div", {"class": "courseblock courseblocktoggle"})

for course in courses:
    # Get title and Credits
    courseTitle = course.find("p", {"class": "courseblocktitle noindent"})
    courseTitle = courseTitle.find("strong")
    courseTitle = courseTitle.text.strip()

    courseCredits = course.find("span", {"class": "credits"}).text.strip()


    # Get Pre Reqs

    extraBlocks = course.find_all("p", {"class": "courseblockextra noindent"})
    hasPreReq = False

    for block in extraBlocks:
        if(block.find("strong")):
            preReq = block
            hasPreReq = True

        

    # hasPreReqs = False

    # for block in extraBlocks:
    #     if (block.find("strong").text == "Prerequisite:"):
    #         hasPreReqs = True
    #         preReq = block.find("a", {"class": "bubblelink code"})
    #         if(preReq):
    #             preReq = preReq.title
    #         else:
    #             # If it is not a link type it is a text type contained in the parent
    #             preReq = block.text
            

                

                


    print(f"Class: {courseTitle}")
    if(hasPreReq):
        print(f"PreRequisites: {preReq}\n")
    else:
        print("NO Pre-Reqs")