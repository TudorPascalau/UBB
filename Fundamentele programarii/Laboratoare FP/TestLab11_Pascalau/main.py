
import unittest

from repository.repo_website import RepositoryWebsitesFile
from service.service_websites import ServiceWebsites
from ui.console import Console
from ui.ui_website import UIWebsite
from validator.validator_website import ValidatorWebsite

#Aplicatia principala

def main():
    #Crearea obiectele ce tin de teste
    loader = unittest.TestLoader()
    suite = loader.discover("teste")
    runner = unittest.TextTestRunner(verbosity=2)
    runner.run(suite)

    #Crearea obiectelor ce tin de website-uri
    filepath_dovzei = r"C:\Users\tudor\Documents\FMI Sem.1\Laboratoare FP\TestLab11_Pascalau\sources\websites.txt"
    repo_websites = RepositoryWebsitesFile(filepath_dovzei)

    validator_website = ValidatorWebsite()
    service_websites = ServiceWebsites(repo_websites, validator_website)

    ui_website = UIWebsite(service_websites)
    console = Console(ui_website)

    #Rulam aplicatia
    console.run()

if __name__ == '__main__':
    main()