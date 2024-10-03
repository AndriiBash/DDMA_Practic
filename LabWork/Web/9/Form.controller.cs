
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System.Xml.Linq;
using WEB_LAB8.Models;

namespace WEB_LAB8.Controllers
{
    public class RegController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
        [HttpPost]
        public ActionResult AuthForm(string username, string password)
        {
            XDocument doc = XDocument.Load("D:\\projects VS\\WEB_LAB8\\acc.xml");
            var users = doc.Descendants("user")
                            .Select(u => new Reg
                            {
                                Role = u.Attribute("role").Value,
                                Username = u.Element("username").Value,
                                Password = u.Element("password").Value
                            })
                            .ToList();

            var user = users.FirstOrDefault(u => u.Username == username && u.Password == password);
            if (user != null)
            {
                if (user.Role == "admin")
                    return View("Admin", users);
                else
                    return View("~/Views/Reg/User.cshtml", user);
            }

            ViewBag.ErrorMessage = "Користувач не знайден або невірний пароль";
            return View("Index");
        }

        [HttpPost]
        public ActionResult AddUser(string newUsername, string newPassword, string newRole)
        {
            XDocument doc = XDocument.Load("D:\\projects VS\\WEB_LAB8\\acc.xml");

            XElement newUser = new XElement("user",
                                    new XAttribute("role", newRole),
                                    new XElement("username", newUsername),
                                    new XElement("password", newPassword));
            doc.Root.Add(newUser);
            doc.Save("D:\\projects VS\\WEB_LAB8\\acc.xml");
            var users = doc.Descendants("user").Select(u => new Reg
            {
                Role = u.Attribute("role").Value,
                Username = u.Element("username").Value,
                Password = u.Element("password").Value
            })
                            .ToList();
            return View("Admin", users);
        }
        [HttpPost]
        public ActionResult DeleteUser(string usernameToDelete)
        {
            XDocument doc = XDocument.Load("D:\\projects VS\\WEB_LAB8\\acc.xml");

            var userToDelete = doc.Descendants("user")
                                   .FirstOrDefault(u => u.Element("username").Value == usernameToDelete);

            if (userToDelete != null)
            {
                userToDelete.Remove();
                doc.Save("D:\\projects VS\\WEB_LAB8\\acc.xml");

            }
            else
                ViewBag.ErrorMessage = "Користувач не знайден";
            var users = doc.Descendants("user")
                               .Select(u => new Reg
                               {
                                   Role = u.Attribute("role").Value,
                                   Username = u.Element("username").Value,
                                   Password = u.Element("password").Value
                               })
                               .ToList();
            return View("Admin", users);
        }

        [HttpPost]
        public ActionResult EditUser(string oldUsername, string newUsername, string newPassword, string newRole)
        {
            XDocument doc = XDocument.Load("D:\\projects VS\\WEB_LAB8\\acc.xml");

            var userToEdit = doc.Descendants("user")
                                 .FirstOrDefault(u => u.Element("username").Value == oldUsername);

            if (userToEdit != null)
            {
                userToEdit.Element("username").Value = newUsername;
                userToEdit.Element("password").Value = newPassword;
                userToEdit.Attribute("role").Value = newRole;

                doc.Save("D:\\projects VS\\WEB_LAB8\\acc.xml");


            }
            else
                ViewBag.ErrorMessage = "Користувач не знайден";
            var users = doc.Descendants("user")
                               .Select(u => new Reg
                               {
                                   Role = u.Attribute("role").Value,
                                   Username = u.Element("username").Value,
                                   Password = u.Element("password").Value
                               })
                               .ToList();
            return View("Admin", users);
        }
    }
}