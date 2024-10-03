using Microsoft.AspNetCore.Mvc;

namespace WEB_LAB8.Controllers
{
    public class FormController : Controller
    {
        public IActionResult Index()
        {
            var model = new Models.Form
            {
                REQUEST_METHOD = HttpContext.Request.Method,
                REMOTE_ADDR = HttpContext.Connection.RemoteIpAddress?.ToString() ?? string.Empty
            };

            return View(model);
        }

        [HttpPost]
        public IActionResult SubmitForm(Models.Form model)
        {
            

            // Зберігаємо значення REMOTE_USER в TempData
            TempData["REMOTE_USER"] = HttpContext.Request.Headers["REMOTE_USER"];

            // Передаємо модель з результатами на нову сторінку
            return RedirectToAction("Result");
        }

        public IActionResult Result()
        {
            // Отримуємо значення REMOTE_USER з TempData
            var remoteUser = TempData["REMOTE_USER"]?.ToString();

            var model = new Models.Form
            {
                REMOTE_USER = remoteUser,
                REQUEST_METHOD = HttpContext.Request.Method,
                REMOTE_ADDR = HttpContext.Connection.RemoteIpAddress?.ToString() ?? string.Empty
            };

            // Повертаємо сторінку з результатами
            return View(model);
        }
    }
}
